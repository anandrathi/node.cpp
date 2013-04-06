#include "event_loop.h"
#include <assert.h>

inline  void CHECK(int r, const char * msg, uv_loop_t* p_uv_loop)  
{
    if (r) { 
    uv_err_t err = uv_last_error(p_uv_loop); 
    fprintf(stderr, "%s: %s\n", msg, uv_strerror(err)); 
    exit(1); 
    }
}
  
inline  void CHECKSTATIC(int r, const char * msg, uv_loop_t* p_uv_loop)  
{
    if (r) {
        uv_err_t err = uv_last_error(p_uv_loop);
        fprintf(stderr, "%s: %s\n", msg, uv_strerror(err)); 
        exit(1); 
    }
}
  
EventLoop::EventLoop()
{
    m_server.data=this;
    m_request_num=0;
}

EventLoop::~EventLoop()
{
    
}


int
EventLoop::Loop(const char* ip, int port)
{
  //parser_settings.on_message_complete = on_message_complete;
  m_uv_loop = uv_default_loop();
  int t_r = uv_tcp_init(m_uv_loop, &m_server);
  CHECK(t_r, "bind", m_uv_loop);
  struct sockaddr_in address = uv_ip4_addr(ip, port);
  t_r = uv_tcp_bind(&m_server, address);
  CHECK(t_r, "bind", m_uv_loop);
  uv_listen((uv_stream_t*)&m_server, 128, on_connect_s);
  LOGF("listening on port %d", port);
  uv_run(m_uv_loop, UV_RUN_DEFAULT);
  return 0;   
}

void EventLoop::on_close_s(uv_handle_t* handle) {
    ClientConnection* client = (ClientConnection*) handle->data;
    LOGF("[ %5d ] connection closed", client->getRequestNum());
    client->getEventLoop()->freeClientConn.push_back(client);
}

uv_buf_t EventLoop::on_alloc_s(uv_handle_t* handle, size_t suggested_size) {
        ClientConnection* client = (ClientConnection*) handle->data;
        uv_buf_t buf;
        buf.base = (char *)client->getInDataBuffer().resizeWriteFromStart(suggested_size);
        buf.len = suggested_size;
        return buf;
}


void EventLoop::on_read_s(uv_stream_t* tcp, ssize_t nread, uv_buf_t buf) {
  size_t parsed;

  ClientConnection* client = (ClientConnection* ) tcp->data;
  LOGF("[ %5d ] on read", client->getRequestNum());

  if (nread >= 0) {
      
    parsed = client->getHttpParser().parse(buf.base, nread);   
    if (parsed < nread) {
      LOG_ERROR("parse error");
      uv_close((uv_handle_t*) client->getHandle(), EventLoop::on_close_s);
    }
  } else {
    uv_err_t err = uv_last_error(client->getEventLoop()->m_uv_loop);
    if (err.code != UV_EOF) {
      UVERR(err, "read");
    }
  }
  //free(buf.base);
}

void EventLoop::on_connect_s(uv_stream_t* server_handle, int status) 
{
  //assert((uv_tcp_t*)server_handle == &m_server);
  EventLoop* pEventLoop = static_cast<EventLoop*>(server_handle->data);
  pEventLoop->on_connect(server_handle, status); 
}

void EventLoop::on_connect(uv_stream_t* server_handle, int status) 
{
   
  m_request_num++;
  ClientConnection* client = 0;
  if(freeClientConn.size()>0) {
    LOGF("[ %5lu ] pull connection", m_request_num);
    client = const_cast<ClientConnection*>(freeClientConn.front());
    freeClientConn.pop_front();
  }
  else{
    LOGF("[ %5lu ] create new connection", m_request_num);
    client = new ClientConnection(this);
  }
  CHECK(status, "connect", m_uv_loop);
  client->setRequestNum(m_request_num);
  LOGF("[ %5lu ] new connection", m_request_num);
  uv_tcp_init(m_uv_loop, client->getHandle());
  http_parser_init(&client->getHttpParser().getParserPlusPlus(), HTTP_REQUEST);

  client->getHttpParser().getParserPlusPlus().data = client;
  client->getHandle()->data = client;

  int r = uv_accept(server_handle, (uv_stream_t*)client->getHandle());
  CHECK(r, "accept", m_uv_loop);

  uv_read_start((uv_stream_t*)client->getHandle(), EventLoop::on_alloc_s, EventLoop::on_read_s);
}

void EventLoop::after_write(uv_write_t* req, int status) {
  CHECK(status, "write", m_uv_loop);
  uv_close((uv_handle_t*)req->handle, EventLoop::on_close_s);
}

