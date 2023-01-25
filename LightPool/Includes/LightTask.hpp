#pragma once

#include <functional>

namespace Light {
    struct Task
    {
        std::function<void()> task;
    };
}