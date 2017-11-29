#ifndef HEADERS_MODEL_THREAD_H_
#define HEADERS_MODEL_THREAD_H_


#include <thread>
#include <iostream>

using namespace std;

class Thread {
protected:
	std::thread thread;

public:
	void start();

	virtual void run() = 0;

	void join();
};

#endif /* HEADERS_MODEL_THREAD_H_ */
