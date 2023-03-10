#pragma once

#include <atomic>

namespace Light
{
    class LightMutex
    {
    private:
        std::atomic<bool> locked{false};
        
    public:
        void lock();
        void unlock();

    public:
        bool isLocked() const {
            return locked;
        }
    };
}
