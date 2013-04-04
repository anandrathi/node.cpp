#ifndef WORKERPOOL_H
#define WORKERPOOL_H
#include "worker.h"
#include "SynchronisedQueue.h"
#include <vector>

class WorkerPool
{
    std::vector<WorkerPtr> m_WorkersArray;
    static WorkerPool *s_WorkerPool;
    int m_size;
    ClientSynchronisedQueue m_queue;
    WorkerPool();
    ~WorkerPool();

public:
    static WorkerPool * GetInstance();
    void CreatePool(size_t size);
    void Start();
    void Shutdown();
    
};

#endif // WORKERPOOL_H
