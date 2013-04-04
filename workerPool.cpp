#include "workerPool.h"

WorkerPool *WorkerPool::s_WorkerPool=0;

WorkerPool::WorkerPool()
{
    
}


WorkerPool* WorkerPool::GetInstance()
{
    if(s_WorkerPool==0)
        s_WorkerPool=new WorkerPool();
    return s_WorkerPool;
}

void WorkerPool::CreatePool(size_t psize)
{
    m_WorkersArray.resize(psize);
    for(size_t i=0;i<psize;i++) {
        m_WorkersArray[i]= WorkerPtr(new Worker(m_queue));
    }
}

void WorkerPool::Start()
{
    for(size_t i=0;i<m_WorkersArray.size();i++) {
        m_WorkersArray[i]->Start();
    }
    
}


void WorkerPool::Shutdown()
{
    for(size_t i=0;i<m_WorkersArray.size();i++) {
        m_WorkersArray[i]->Shutdown();
    }
}

WorkerPool::~WorkerPool()
{
    
}
