#ifdef LIGHTPOOL_EXPORTS
	#define LIGHTPOOL_API __declspec(dllexport)
#else
	#define LIGHTPOOL_API __declspec(dllimport)
#endif

#include <atomic>

class ILightMutex
{
	std::atomic<bool> locked{ false };
public:
	virtual void lock();
	virtual void unlock();

private:

};

class LightMutex : public ILightMutex {
	//rest of the code
};

__declspec(dllexport) ILightMutex* Create() {
	return new LightMutex();
}

__declspec(dllexport) void Destroy(ILightMutex* instance) {
	delete instance;
}