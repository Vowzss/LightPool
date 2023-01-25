#include "Includes/LightPool.hpp"

#include <iostream>

namespace Light
{
    LightPool::LightPool()
    {
    }

    LightPool::~LightPool()
    {
        // wait for last task to finish before deleting threads
        for (auto thr : pool)
        {
            delete thr;
        }
    }

    std::vector<LightThread*> LightPool::getPool()
    {
        return pool;
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
                break;
            }
        }
    }

    void LightPool::stop()
    {
        shutdown = true;
    }

    bool LightPool::shouldStop()
    {
        return shutdown;
    }

    void LightPool::registerTask(Task task)
    {
        taskLock.lock();
        tasks.push(task);
        taskLock.unlock();

        taskCondition.notify_one();
    }

    Task LightPool::queryTask(LightThread* pThread, std::string pName)
    {
        const Task task = tasks.front();
        tasks.pop();
        return task;
    }

    LightMutex& LightPool::getQueryLock()
    {
        return queryLock;
    }

    LightMutex& LightPool::getTaskLock()
    {
        return taskLock;
    }

    std::queue<Task> LightPool::getTasks()
    {
        return tasks;
    }
}
