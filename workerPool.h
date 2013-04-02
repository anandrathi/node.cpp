#ifndef WORKERPOOL_H
#define WORKERPOOL_H
#include "worker.h"
#include "SynchronisedQueue.h"
#include <vector>


class WorkerPool
{
    std::vector<worker*> WorkersArray;
    static WorkerPool *s_WorkerPool;
    int m_size;
    ClientSynchronisedQueue m_queue;
    WorkerPool();
    ~WorkerPool();

public:
    static WorkerPool * GetInstance();
    void CreatePool(int size);
    void Start();
    void Shutdown();
    
};

#endif // WORKERPOOL_H
