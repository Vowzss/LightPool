#include <string>
#include <iostream>

#include "../includes/light_pool.hpp"

#define MAX_THREADS 10

void sayHello() {
	std::cout << "Hello!" << std::endl;
}

void sayGoodbye() {
	std::cout << "Goodbye!" << std::endl;
}

int main() {
	// creating pool instance
	LP::LightPool l_pool;

	// registering MAX_THREADS threads in pool
	for (int i = 0; i < MAX_THREADS; i++) {
		l_pool.registerThread(new LP::LightThread(l_pool, std::to_string(i)));
	}

	// registering MAX_THREADS tasks in pool -> if i multiple of 2 then register "sayHello" task if not register "sayGoodbye" task
	for (int i = 0; i < MAX_THREADS; i++) {
		if (i % 2) {
			l_pool.registerTask(LP::Task { []() { sayGoodbye(); }});
		} else {
			l_pool.registerTask(LP::Task{ []() { sayHello(); } });
		}
	}

	// waits for all the tasks to be executed by threads
	while (!l_pool.getTasks().empty());

	// stopping pools, tells threads to stop looking for tasks
	l_pool.stop();
	return 1;
}