#include "../includes/light_thread.hpp"
#include "../includes/light_pool.hpp"

namespace LP {
	LightThread::LightThread(LightPool& pPool, const std::string& pName) {
		name = pName;
		
		thread = std::thread([&]() {
			while (!pPool.shouldStop()) {
				pPool.getQueryLock().lock();

				while (pPool.getTasks().empty()) {
					if (pPool.shouldStop()) {
						pPool.getQueryLock().unlock();
						return;
					}
				}

				Task rt = pPool.queryTask(this, name);
				pPool.getQueryLock().unlock();
				rt.task();
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
}