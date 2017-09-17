#include "../../headers/Model/thread.h"

Thread::Thread() {

}

void Thread::crear(void *funcion(void *tharg), void *args){

	int rc = pthread_create(&thread,NULL,funcion,args);
}

void Thread::terminar(){

	pthread_exit(NULL);
}

Thread::~Thread() {

}

