#include <string>
#include <iostream>

#include "Includes/LightPool.hpp"

// Exemples of allocated values, it doesn't need to rely on it. (Check your system specs for safetiness)
constexpr int EX_MAX_THREADS = 20;
constexpr int EX_MAX_TASKS = 90;

void sayHello() {
	std::cout << "Hello!" << std::endl;
}

void sayGoodbye() {
	std::cout << "Goodbye!" << std::endl;
}

int main() {
	// creating pool instance
	Light::LightPool l_pool;

	// registering EX_MAX_THREADS threads in pool
	for (int i = 0; i < EX_MAX_THREADS; i++) {
		l_pool.registerThread(new Light::LightThread(l_pool, i));
	}

	// registering EX_MAX_TASKS tasks in pool -> if i multiple of 2 then register "sayHello" task if not register "sayGoodbye" task
	for (int i = 0; i < EX_MAX_TASKS; i++) {
		if (i % 2) {
			l_pool.registerTask(new Light::Task("HelloTask" + std::to_string(i), [] { sayHello(); }));
		} else {
			l_pool.registerTask(new Light::Task("GoodbyeTask" + std::to_string(i), [] { sayGoodbye(); }));
		}
		
		// sync execution (no data races) ex: std::cout in our case
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	// stopping pools, tells threads to stop looking for tasks
	l_pool.stopPool();
	return 1;
}