#include <iostream>
#include "../../headers/Model/servidorBuilder.h"
#include "../../headers/Model/consola.h"
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


