#include "dll/pch.h"

#include "thread/light_thread.h"
LightThread::LightThread(LightPool& pPool, const std::string& pName) {
	name = pName + " - Thread";

	thread = std::thread([&]() {
		while (!pPool.shouldStopPool()) {
			pPool.queryTask(this, name)();
		}
		});
}

LightThread::~LightThread() {
}