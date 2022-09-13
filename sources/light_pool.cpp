#include "../includes/light_pool.hpp"

#include <iostream>

namespace LP {
	LightPool::LightPool() {
	}

	LightPool::~LightPool() {
		// wait for last task to finish before deleting threads
		for (LP::LightThread* thr : pool) {
			thr->getThread().join();
		}
		
		for (LightThread* thr : pool) {
			delete thr;
		}
	}

	std::vector<LightThread*> LightPool::getPool() {
		return pool;
	}

	void LightPool::registerThread(LightThread* pThread) {
		pool.push_back(pThread);
	}

	void LightPool::unregisterThread(LightThread* pThread) {
		for (int i = 0; i < pool.size(); i++) {
			if (pThread->getName() == pool.at(i)->getName()) {
				pool.erase(pool.begin() + i);
				break;
			}
		}
	}

	void LightPool::stop() {
		shutdown = true;
	}

	bool LightPool::shouldStop() {
		return shutdown;
	}

	void LightPool::registerTask(Task task) {
		taskMtx.lock();
		tasks.push(task);
		taskMtx.unlock();

		taskCondition.notify_one();
	}

	Task LightPool::queryTask(LightThread* pThread, std::string pName) {
		queryMtx.lock();

		std::cout << pThread->getName() << " was assigned a task!" << std::endl;

		pThread->setWorking(false);

		while (tasks.empty()) {
			if (!pThread->getWorking()) {
				pThread->setWorking(false);
			}
		}

		pThread->setWorking(true);

		Task task = tasks.front();
		tasks.pop();
		queryMtx.unlock();
		return task;
	}
}