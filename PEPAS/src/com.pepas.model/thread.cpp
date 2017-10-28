#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/thread.h"

void Thread::start() {
	thread = std::thread(&Thread::run, this);
}

void Thread::join() {
	this->thread.join();
}


