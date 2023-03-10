#include <utility>

#include "Includes\LightTask.hpp"

#include <iostream>

using namespace Light;
Task::Task(std::string pName, std::function<void()> pFunction) : function(std::move(pFunction)), name(std::move(pName))
{
}

void Task::execute(const std::string& pThreadName) const
{
    std::cout << "Executing \"" << getName() << "\" task on \"" << pThreadName << "\" ";
    function();
}

