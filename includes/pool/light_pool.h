#ifdef LIGHTPOOL_EXPORTS
	#define LIGHTPOOL_API __declspec(dllexport)
#else
	#define LIGHTPOOL_API __declspec(dllimport)
#endif

#include <vector>
#include <iostream>
#include <queue>
#include <condition_variable>

typedef std::function<void()> Task;

#include "thread/light_thread.h"
#include "mutex/light_mutex.h"

class LightPool
{
public:
	LightPool();
	~LightPool();

	void registerThread(LightThread* pThread);
	void unregisterThread(LightThread* pThread);

	std::vector<LightThread*> getPool();

	void stop();
	bool shouldStop();

	void registerTask(Task task);

	Task queryTask(LightThread* pThread, std::string pName);

	bool isRegistering = true;
private:
	AtomicMutex queryMtx;
	AtomicMutex taskMtx;

	std::vector<LightThread*> pool;
	std::queue<Task> tasks;

	std::atomic_bool shutdown{ false };
	std::condition_variable taskCondition;
};