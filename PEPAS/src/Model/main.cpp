#include <iostream>
#include "../../headers/Model/servidorBuilder.h"
#include "../../headers/Vista/consola.h"
#include "../../headers/Model/logger.h"


//#include "../../tests/baseDeDatosTest.cpp"
#include "../../tests/threadsTests.cpp"
#include "../../headers/Vista/ConsolaThread.h"
#include "../../headers/Model/EscuchaThread.h"
#include <cstdlib>
#include <pthread.h>
using namespace std;

int main(int argc, char *argv[]) {


	crear_logger();
	Consola* consola = new Consola();

	if (argc !=2)
    	consola->cargarPaginaCrearServidor("1");
    else
    	consola->cargarPaginaCrearServidor(argv[1]);

    ConsolaThread intefazMenu(consola);
    Servidor* servidor = consola->obtenerServidorController()->obtenerServidor();


    EscuchaThread escuchaThread(servidor);
    intefazMenu.start();
    //consola->abrirServidorAClientes();
    escuchaThread.start();
    intefazMenu.join();
    escuchaThread.join();
	cerrar_logger();
	delete consola;
	/////////////////////////////////////////////////////////////////////////////////////

	return 0;

}


