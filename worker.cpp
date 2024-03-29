#include "worker.h"
#include "client_connection.h"
#include "libjspp_http_parser.h"

Worker::Worker(ClientSynchronisedQueue&  p_ClientSynchronisedQueue):
m_ClientSynchronisedQueue(p_ClientSynchronisedQueue)
{
}

Worker::~Worker()
{
}

bool Worker::sleep(boost::system_time & t)
{
    if(m_thread_impl!=0) {
        m_thread_impl->sleep(t);
        return true;
    }
    return false;
}

void Worker::Start()
{   if(m_thread_impl==0)
        m_thread_impl =  boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Worker::Run, this)));
}

void Worker::Join() 
{
    if(m_thread_impl!=0)
        m_thread_impl->join();
}

void Worker::Shutdown() 
{
    m_stop=true;
    if(m_thread_impl!=0){
        m_thread_impl->interrupt();
    }
}

void Worker::Run()
{   m_ClientConnection=0;
    if(m_stop)
        return; 
    m_ClientConnection=m_ClientSynchronisedQueue.Dequeue();
    if(m_stop)
        return; 
    if(m_ClientConnection) {
        
    }
}


