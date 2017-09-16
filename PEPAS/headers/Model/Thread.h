#ifndef HEADERS_MODEL_THREAD_H_
#define HEADERS_MODEL_THREAD_H_

#include <pthread.h>
#include <iostream>
#include <cstdlib>

class Thread {

private:
	//Tipo de dato manejado para usar Threads: unsigned long int.
	pthread_t thread;

public:

	//Metodo para crear un thread nuevo. Debe ser llamado por quien quiere crear un nuevo hilo.
	//Recibe por parametro un puntero Void que representa una funcion y un puntero Void que son los argumentos de esa funcion
	//No se que es threadid (supongo que un id que maneja pthreads)
	//La funcion debe ser proporcionada por quien maneja los threads.
	void crear(void* funcion(void* threadid),void *args);

	//METODO ESTATICO (PUEDE SER LLAMADO DE CUALQUIER LUGAR EN CUALQUIER MOMENTO SIN INSTANCIAR LA CLASE THREAD
	//Se debe usar al final de cada proceso donde esta vivo quien maneja los threads
	static void terminar();
	Thread();
	~Thread();
};

#endif /* HEADERS_MODEL_THREAD_H_ */
