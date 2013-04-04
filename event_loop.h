#ifndef EVENTLOOP_H
#define EVENTLOOP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include "ClientConnCache.h"

class EventLoop
{
    CLIENTCONNECTIONLIST freeClientConn; 
public:
    EventLoop();
    ~EventLoop();
    static void on_close_s(uv_handle_t* handle) ;
    static uv_buf_t on_alloc_s(uv_handle_t* handle, size_t suggested_size);
    static void on_read_s(uv_stream_t* tcp, ssize_t nread, uv_buf_t buf);
    static void on_connect_s(uv_stream_t* server_handle, int status) ;
    void on_connect(uv_stream_t* server_handle, int status) ;
    void after_write(uv_write_t* req, int status);
    int Loop(const char* ip, int port);
    
    private://  Temprory 
        int t_n;
        int t_i;
        int t_r ;
    private://  Members
        uv_loop_t* m_uv_loop;
        uv_tcp_t m_server;
        size_t m_request_num;
};

#endif // EVENTLOOP_H
