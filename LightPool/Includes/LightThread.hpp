#pragma once

#include <string>
#include <thread>

namespace Light
{
    class LightPool;

    class LightThread
    {
    private:
        int id;
        std::string name;
        std::thread thread;
        
    public:
        LightThread(LightPool& pPool, int pId);
        ~LightThread();

    public:
        std::string getName() {
            return name;
        }
        
        std::thread& getThread() {
            return thread;
        }
    };
}
