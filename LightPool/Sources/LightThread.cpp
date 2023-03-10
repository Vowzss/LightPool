#include <iostream>

#include "Includes/LightThread.hpp"
#include "Includes/LightPool.hpp"

using namespace Light;
LightThread::LightThread(LightPool& pPool, int pId) : id(std::move(pId)), name("Thread ID-" + std::to_string(id))
{
    thread = std::thread([&]
    {
        while (!pPool.shouldStop())
        {
            pPool.getQueryLock().lock();

            while (pPool.getTasks().empty())
            {
                std::cout << getName() << " did not find a task..." << std::endl;
                if (pPool.shouldStop())
                {
                    pPool.getQueryLock().unlock();
                    return;
                }
            }

            const Task* task = pPool.queryTask();
            pPool.getQueryLock().unlock();

            try {
                if(task == nullptr) return;
                task->execute(getName());
                delete task;
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
    });
}

LightThread::~LightThread()
{
    thread.join();
}



