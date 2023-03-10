#pragma once

#include <functional>
#include <string>

namespace Light {
    class Task
    {
    private:
        std::function<void()> function;
        std::string name;

    public:
        Task(std::string pName, std::function<void()> pFunction);
        ~Task() = default;

    public:
        void execute(const std::string& pThreadName) const;
        
    public:
        std::function<void()> getFunction() const {
            return function;
        }

        std::string getName() const {
            return name;
        }
    };
}
