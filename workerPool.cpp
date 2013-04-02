#include "workerPool.h"

WorkerPool *WorkerPool::s_WorkerPool=0;

WorkerPool* WorkerPool::GetInstance()
{
    if(s_WorkerPool==0)
        s_WorkerPool=new WorkerPool();
    return s_WorkerPool;
}

void WorkerPool::CreatePool(int psize)
{
    WorkersArray.size(psize);
    for(int i=0;i<psize;i++) {
        WorkersArray[i]= new worker(m_queue);
    }
}

void WorkerPool::Start()
{
    for(int i=0;i<psize;i++) {
        WorkersArray[i]->Start();
    }
    
}

void WorkerPool::ShutDown() 
{
    for(int i=0;i<psize;i++) {
        WorkersArray[i]->Start();
    }
}

void WorkerPool::Shutdown()
{
    for(int i=0;i<psize;i++) {
        WorkersArray[i]->Start();
    }
    
}

~WorkerPool();
