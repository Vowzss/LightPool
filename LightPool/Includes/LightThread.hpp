#pragma once

#include <string>
#include <condition_variable>
#include <thread>

namespace Light
{
    class LightPool;

    class LightThread
    {
    public:
        LightThread(LightPool& pPool, const std::string& pNam);
        ~LightThread();

        std::string getName();
        std::thread& getThread();

    private:
        std::string name;
        std::thread thread;
    };
}
