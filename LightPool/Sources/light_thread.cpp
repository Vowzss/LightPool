#include "../Includes/light_thread.hpp"
#include "../Includes/light_pool.hpp"

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

				Task tk = pPool.queryTask(this, name);
				pPool.getQueryLock().unlock();
				
				try {
					tk.task();
				}
				catch (const std::exception&) {
					continue;
				}

			}
		});
	}

	LightThread::~LightThread() {
		thread.join();
	}

	std::string LightThread::getName() {
		return name;
	}

	std::thread& LightThread::getThread() {
		return thread;
	}
}