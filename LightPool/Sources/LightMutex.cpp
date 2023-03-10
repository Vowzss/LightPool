#include "Includes/LightMutex.hpp"

using namespace Light;
void LightMutex::lock()
{
    while (locked.exchange(true, std::memory_order_relaxed))
        std::atomic_thread_fence(std::memory_order_acquire);
}

void LightMutex::unlock()
{
    std::atomic_thread_fence(std::memory_order_release);
    locked.store(false, std::memory_order_relaxed);
}

