#include <iostream>
#include "../../headers/Model/servidorBuilder.h"
#include "../../headers/Vista/consola.h"
#include "../../headers/Model/logger.h"
using namespace std;

int main() {

	crear_logger();
	Consola* consola = new Consola();

	consola->cargarPaginaCrearServidor();
	while(!consola->getTerminado()){

		consola->cargarPagina(0);
	}

	delete consola;
	cerrar_logger();

	return 0;
}


