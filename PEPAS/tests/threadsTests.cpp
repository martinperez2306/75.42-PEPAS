#include "../headers/Model/Thread.h"
#include <iostream>
using namespace std;

class ThreadsTests{

private:
	Thread thread;
	Thread thread2;

public:

	ThreadsTests(){

	}

	static void *PrintHello(void *threadid) {
			   long tid;
			   tid = (long)threadid;
			   cout << "Hello World! Thread ID, " << tid << endl;
			   pthread_exit(NULL);
			}

	void crearUnNuevoThreadYCerrarloLuegoDeMain(){

		cout<<"creando thread 1"<<endl;
		thread.crear(PrintHello,NULL);
		cout<<"creadno thread 2"<<endl;
		thread2.crear(PrintHello,NULL);

	}
};



