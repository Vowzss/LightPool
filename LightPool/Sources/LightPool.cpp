#include "Includes/LightPool.hpp"

using namespace Light;
LightPool::~LightPool()
{
    // wait for last task to finish before deleting threads
    for (const auto thread : pool) {
        delete thread;
    }
}

void LightPool::registerThread(LightThread* pThread)
{
    pool.push_back(pThread);
}

void LightPool::unregisterThread(LightThread* pThread)
{
    for (int i = 0; i < pool.size(); i++)
    {
        if (pThread->getName() == pool.at(i)->getName())
        {
            pool.erase(pool.begin() + i);
            delete pThread;
            break;
        }
    }
}

void LightPool::unregisterThreads()
{
    for (int i = 0; i < pool.size(); i++)
    {
        delete pool[i];
        pool.erase(pool.begin() + i);
    }
}

void LightPool::registerTask(Task* pTask)
{
    taskLock.lock();
    tasks.push(pTask);
    taskLock.unlock();

    taskCondition.notify_one();
}

Task* LightPool::queryTask()
{
    if(tasks.empty()) return nullptr;
    Task* task = tasks.front();
    tasks.pop();
    return task;
}

