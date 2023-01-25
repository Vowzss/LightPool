#pragma once

#include <atomic>

namespace Light
{
    class LightMutex
    {
    public:
        void lock();
        void unlock();

    private:
        std::atomic<bool> locked{false};
    };
}
