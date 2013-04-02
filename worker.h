#ifndef WORKER_H
#define WORKER_H
#include <boost/thread.hpp>
#include "SynchronisedQueue.h"

class Worker 
{
    boost::thread* m_thread_impl;
    bool m_stop;
    ClientSynchronisedQueue&  m_ClientSynchronisedQueue;
    ClientConnection* m_ClientConnection;
    void Run();
public:
    Worker(ClientSynchronisedQueue&  p_ClientSynchronisedQueue);
    void Start();
    void ShutDown();
    bool sleep(boost::system_time & t);
    ~Worker();
};

#endif // WORKER_H
