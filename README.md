<div align="center">

# LightPool
</div>

**LightPool is lightweight thread and pooling system originally made for loading and parsing data.**<br/>

# Run
Open **LightPool.sln** solution using Visual Studio (recommended version 2019)

# Usage
First of all you need to instanciate a pool the following way.<br/>
```cpp
#include "../Includes/light_pool.hpp"
using namespace LP;

LightPool pool;
```

To register thread, this very simple, you can either do a for loop or register it by hand dependin on your needs.<br/>
MAX_THREADS in our case should be equals or less than what your current system can handle for safety reasons.<br/>
```cpp
for (int i = 0; i < MAX_THREAD; i++) {
	pool.registerThread(new LightThread(pool, std::to_string(i)));
}
```

To register a task, same as before, the method is self explanatory.<br/>
MAX_TASKS in our case can be equal to anything, this is an exemple you don't necessarily need to use a for loop.<br/>
To register a Task, use a lambda so you can register any functions with args or not.<br/>
Two simple functions registered here that will print on the console some text.<br/>
We make the thread sleep for 1 ms, but not necessary at all.<br/>
```cpp
for (int i = 0; i < MAX_TASKS; i++) {
    if (i % 2) {
        pool.registerTask(Task { []() { sayGoodbye(); }});
    } else {
        pool.registerTask(Task{ []() { sayHello(); } });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
```

As an example, since the lib is not supposed to be used all alone, it will keep the program running.<br/>
Itc an be replaced by an if condition to check if the pool is empty or not and decide what do to base on the result.<br/>
```cpp
while (!pool.getTasks().empty());
```

To shutdown the pool, very simple, call the stop() method.<br/>
This will tell the thread(s) to finish their current task and then will delete them.<br/>
Note that once the stop() method was called, even if there are remaining tasks waiting to be processed in queued, they will be ignored for obvious reasons, make sure you call it at the right place.<br/>
```cpp
pool.stop();
```

# Other information
The **Task** object is a simple structure holding a std::function than returns void, it might be restrictive but usually you don't need to return values when doing multithreaded apps, the response can be bottled in the registered function itself.<br/>
```cpp
struct Task
{
    std::function<void()> task;
};
```

The **LightMutex** is a very user friendly implementation of the std::mutex, but with a tighter range of utility. Regarding the lightweight aspect, you cannot do better.<br/>
```cpp
class LightMutex
{
public:
    void lock();
    void unlock();

private:
    std::atomic<bool> locked{ false };
};

void LightMutex::lock() {
    while (locked.exchange(true, std::memory_order_relaxed));
    std::atomic_thread_fence(std::memory_order_acquire);
}

void LightMutex::unlock() {
    std::atomic_thread_fence(std::memory_order_release);
    locked.store(false, std::memory_order_relaxed);
}
```

# Exemples
You can head to the following folder to have a better view of the whole library in action.<br/>
&nbsp;&nbsp; -> .cpp files located in sources/<br/>
&nbsp;&nbsp; -> .hpp files located in Includes/<br/>

Exemple file is sources/ named **"light_pool_test.cpp"** (no header file for this one)

# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.<br/>
Please make sure to update tests as appropriate.<br/>