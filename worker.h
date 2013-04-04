#ifndef WORKER_H
#define WORKER_H
#include <boost/thread.hpp>
#include "SynchronisedQueue.h"
#include <boost/shared_ptr.hpp>

class Worker
{
    boost::thread* m_thr;
    boost::shared_ptr<boost::thread> m_thread_impl;
    bool m_stop;
    ClientSynchronisedQueue&  m_ClientSynchronisedQueue;
    
    void Run();

    //Temprory variable 
    ClientConnection* m_ClientConnection;
public:
    Worker(ClientSynchronisedQueue&  p_ClientSynchronisedQueue);
    void Start();
    void Shutdown();
    bool sleep(boost::system_time & t);
    void Join();
    ~Worker();
};

typedef boost::shared_ptr<Worker> WorkerPtr;

#endif // WORKER_H
