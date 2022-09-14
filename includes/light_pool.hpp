#pragma once

#include <vector>
#include <queue>
#include <functional>

#include "light_mutex.hpp"
#include "light_thread.hpp"

namespace LP {

	struct Task
	{
		std::function<void()> task;
	};

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

		LightMutex& getQueryLock();
		LightMutex& getTaskLock();

		std::queue<Task> getTasks();

	private:
		LightMutex queryLock;
		LightMutex taskLock;

		std::vector<LightThread*> pool;
		std::queue<Task> tasks;

		std::atomic_bool shutdown{ false };
		std::condition_variable taskCondition;
	};
}