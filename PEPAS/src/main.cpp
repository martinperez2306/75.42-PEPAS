#include <iostream>

#include <pthread.h>
#include "../headers/com.pepas.parser/ClienteParser.h"
#include "../headers/com.pepas.controllers/clienteController.h"
#include "../headers/com.pepas.view/consola.h"
using namespace std;
Consola *consola

void *cargarPagina(void *threadid) {

	consola->cargarPagina();
	pthread_exit(NULL);
}

void *escucharMensajes(void *threadid) {
	consola->clienteController->cliente->socketCliente->Escuchar(consola->clienteController->cliente->socketFD, 1);
}

int main(int argc, char *argv[]) {
	consola = new Consola();

	pthread_t thread_enviar, thread_recibir;
	int rc;

	rc = pthread_create(&thread_enviar, NULL, cargarPagina, NULL);
	 if (rc) {
		cout << "Error creando thread enviar" << rc << endl;
		exit(-1);
	}
	rc = pthread_create(&thread_enviar, NULL, escucharMensajes, NULL);
		if (rc) {
			cout << "Error creando thread recibir" << rc << endl;
			exit(-1);
		}
	pthread_exit(NULL);

}




