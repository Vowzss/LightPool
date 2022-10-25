#pragma once

#include <atomic>

namespace LP {
	class LightMutex
	{
	public:
		void lock();
		void unlock();

	private:
		std::atomic<bool> locked{ false };
	};
}