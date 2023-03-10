#pragma once

#include <condition_variable>
#include <iostream>
#include <ostream>
#include <vector>
#include <queue>

#include "LightMutex.hpp"
#include "LightThread.hpp"
#include "LightTask.hpp"

namespace Light
{
    class LightPool
    {
    private:
        LightMutex queryLock;
        LightMutex taskLock;

        std::vector<LightThread*> pool;
        std::queue<Task*> tasks;

        std::atomic_bool shutdown{false};
        std::condition_variable taskCondition;
        
    public:
        LightPool() = default;
        ~LightPool();

    public:
        void registerThread(LightThread* pThread);
        void unregisterThread(LightThread* pThread);
        void unregisterThreads();
        
        void registerTask(Task* pTask);
        Task* queryTask();

    public:
        std::vector<LightThread*> getPool() const
        {
            return pool;
        }
        
        LightMutex& getQueryLock() {
            return queryLock;
        }
        
        LightMutex& getTaskLock() {
            return taskLock;
        }

        std::queue<Task*> getTasks() const {
            return tasks;
        }
        
        void stopPool() {
            std::cout << "Shutting down thread pool!" << std::endl;
            shutdown = true;
            unregisterThreads();
        }

        bool shouldStop() const {
            return shutdown;
        }
    };
}
