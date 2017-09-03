#include <iostream>
#include "servidorBuilder.h"
#include "consola.h"
using namespace std;

int main() {

	Consola* consola = new Consola();

	consola->cargarPaginaCrearServidor();
	while(!consola->getTerminado()){

		consola->cargarPagina(0);
	}

	delete consola;

	return 0;
}


