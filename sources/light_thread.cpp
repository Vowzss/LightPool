#include "../includes/light_thread.hpp"
#include "../includes/light_pool.hpp"

namespace LP {
	LightThread::LightThread(LightPool& pPool, const std::string& pName) {
		name = pName;

		thread = std::thread([&]() {
			while (!pPool.shouldStop()) {
				pPool.queryTask(this, name)();
			}
		});
	}

	LightThread::~LightThread() {
	}

	std::string LightThread::getName() {
		return name;
	}

	std::thread& LightThread::getThread() {
		return thread;
	}

	bool LightThread::getWorking() {
		return isWorking;
	}

	void LightThread::setWorking(const bool& pIsWorking) {
		isWorking = pIsWorking;
	}
}