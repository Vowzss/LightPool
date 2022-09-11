#pragma once

#ifdef LIGHTPOOL_EXPORTS
	#define LIGHTPOOL_API __declspec(dllexport)
#else
	#define LIGHTPOOL_API __declspec(dllimport)
#endif

#include <string>
#include <thread>
#include <functional>

#include "pool/light_pool.h"
class ILightThread
{
	class LightPool;

public:
	virtual std::string getName();
	virtual std::thread& getThread();
	virtual bool getWorking();
	virtual void setWorking(const bool& pIsWorking);

private:
	std::string name;
	std::thread thread;

	bool isWorking = false;
};

class LightThread : public ILightThread {
	name = pName + " - Thread";

	thread = std::thread([&]() {
		while (!pPool.shouldStopPool()) {
			pPool.queryTask(this, name)();
		}
		});
};

__declspec(dllexport) ILightThread* Create(LightPool& pPool, const std::string& pName) {
	return new LightThread(pPool, pName);
}

__declspec(dllexport) void Destroy(ILightThread* instance) {
	delete instance;
}