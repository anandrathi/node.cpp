#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include "Buffer.h"
#include "libjspp_http_parser.h"
#include "uv/include/uv.h"
#define UVERR(err, msg) fprintf(stderr, "%s: %s\n", msg, uv_strerror(err))
#define LOG_ERROR(msg) puts(msg);
#define LOG(msg) puts(msg);
#define LOGF(fmt, params...) printf(fmt "\n", params);

class EventLoop;
class ClientConnection
{
    int m_fd;
    octetBuffer m_vecDataIn;
    octetBuffer m_vecDataOut;
    HttpParser m_HttpParser;
    uv_tcp_t m_handle;
    int m_request_num;
    uv_write_t m_write_req;
    EventLoop * m_EventLoop;
public:
    ClientConnection(EventLoop* p_EventLoop);
    ~ClientConnection();
    inline int getRequestNum(){return m_request_num;}
    inline void setRequestNum(int num){m_request_num=num;}
    inline uv_tcp_t* getHandle(){ return &m_handle;}
    inline EventLoop*  getEventLoop(){return m_EventLoop;}
    inline octetBuffer& getInDataBuffer(){return m_vecDataIn;}
    inline octetBuffer& getOutDataBuffer(){return m_vecDataOut;}

    inline HttpParser& getHttpParser(void) {return m_HttpParser;}
    inline int& getFD(){return m_fd;}
    inline void setFD(int p_fd){m_fd=p_fd;}
    void setDataIN(char * p_data, size_t p_size) { m_vecDataIn.setData(p_data, p_size);  }
    void setDataOut(char * p_data, size_t p_size) { m_vecDataOut.setData(p_data, p_size); }
    void PushDataIN(char * p_data, size_t p_size) { m_vecDataIn.PushData(p_data, p_size); }
    void PushDataOut(char * p_data, size_t p_size) { m_vecDataOut.PushData(p_data, p_size); }

};

#endif // CLIENTCONNECTION_H
