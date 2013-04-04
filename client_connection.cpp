#include "client_connection.h"

ClientConnection::ClientConnection(EventLoop* p_EventLoop):m_EventLoop(p_EventLoop)
{
    m_HttpParser.Init(HTTP_REQUEST);
}

ClientConnection::~ClientConnection()
{
}

