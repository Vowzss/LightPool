#pragma once

#include <string>
#include <condition_variable>
#include <thread>

namespace LP {
	class LightPool;

	class LightThread
	{
	public:
		LightThread(LightPool& pPool, const std::string& pNam);
		~LightThread();

		std::string getName();
		std::thread& getThread();
		bool getWorking();
		void setWorking(const bool& pIsWorking);

	private:
		std::string name;
		std::thread thread;

		bool isWorking = false;
	};
}