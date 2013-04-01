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
    ParserPlusPlus m_ParserPlusPlus;
    uv_tcp_t m_handle;
    int m_request_num;
    uv_write_t m_write_req;
    EventLoop * m_EventLoop;
public:
    ClientConnection(){};
    ~ClientConnection();
    int getRequestNum(){return m_request_num;}
    void setRequestNum(int num){m_request_num=num;}
    uv_tcp_t* getHandle(){ return &m_handle;}
    EventLoop*  getEventLoop(){return m_EventLoop;}
    octetBuffer& getInDataBuffer(){return m_vecDataIn;}
    octetBuffer& getOutDataBuffer(){return m_vecDataOut;}

    ParserPlusPlus& getParserPlusPlus(void) {return m_ParserPlusPlus;}
    int& getFD(){return m_fd;}
    void setFD(int p_fd){m_fd=p_fd;}
    void setDataIN(char * p_data, size_t p_size)
    { 
        m_vecDataIn.setData(p_data, p_size);
    }
    void setDataOut(char * p_data, size_t p_size)
    { 
        m_vecDataOut.setData(p_data, p_size);
    }
    void PushDataIN(char * p_data, size_t p_size)
    { 
        m_vecDataIn.PushData(p_data, p_size);
    }
    void PushDataOut(char * p_data, size_t p_size)
    { 
        m_vecDataOut.PushData(p_data, p_size);
    }

};

#endif // CLIENTCONNECTION_H
