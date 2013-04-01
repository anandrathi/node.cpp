#include "event_loop.h"

EventLoop::EventLoop()
{
}

EventLoop::~EventLoop()
{
    
}


int
EventLoop::Loop()
{
  parser_settings.on_message_complete = on_message_complete;
  uv_loop = uv_default_loop();
  int r = uv_tcp_init(uv_loop, &server);
  CHECK(r, "bind");
  struct sockaddr_in address = uv_ip4_addr("0.0.0.0", 8000);
  r = uv_tcp_bind(&server, address);
  CHECK(r, "bind");
  uv_listen((uv_stream_t*)&server, 128, on_connect);
  LOG("listening on port 8000");
  uv_run(uv_loop);
    
}

void EventLoop::on_close(uv_handle_t* handle) {
    ClientConnection* client = (ClientConnection*) handle->data;
    LOGF("[ %5d ] connection closed", client->getRequestNum());
    client->getEventLoop()->freeClientConn.push_back(client);
}
uv_buf_t EventLoop::on_alloc(uv_handle_t* handle, size_t suggested_size) {
        ClientConnection* client = (ClientConnection*) handle->data;
        uv_buf_t buf;
        buf.base = (char *)client->getInDataBuffer().resizeWriteFromStart(suggested_size);
        buf.len = suggested_size;
        return buf;
}

void EventLoop::on_read(uv_stream_t* tcp, ssize_t nread, uv_buf_t buf) {
  size_t parsed;

  ClientConnection* client = (ClientConnection* ) tcp->data;
  LOGF("[ %5d ] on read", client->getRequestNum());

  if (nread >= 0) {
    parsed = client->getParserPlusPlus().m_Parser->parse(buf.base, nread);   
    //parsed = http_parser_execute(&client->parser, &parser_settings, buf.base, nread);
    if (parsed < nread) {
      LOG_ERROR("parse error");
      uv_close((uv_handle_t*) client->getHandle(), on_close);
    }
  } else {
    uv_err_t err = uv_last_error(client->getEventLoop()->m_uv_loop);
    if (err.code != UV_EOF) {
      UVERR(err, "read");
    }
  }
  //free(buf.base);
}


void EventLoop::on_connect(uv_stream_t* server_handle, int status) 
{
  CHECK(status, "connect");
  assert((uv_tcp_t*)server_handle == &server);

  client_t* client = (client_t*)malloc(sizeof(client_t));
  client->request_num = request_num;
  request_num++;

  LOGF("[ %5d ] new connection", request_num);

  uv_tcp_init(uv_loop, &client->handle);
  http_parser_init(&client->parser, HTTP_REQUEST);

  client->parser.data = client;
  client->handle.data = client;

  int r = uv_accept(server_handle, (uv_stream_t*)&client->handle);
  CHECK(r, "accept");

  uv_read_start((uv_stream_t*)&client->handle, on_alloc, on_read);
}

void after_write(uv_write_t* req, int status) {
  CHECK(status, "write");
  uv_close((uv_handle_t*)req->handle, on_close);
}

