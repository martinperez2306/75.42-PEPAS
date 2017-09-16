#include <iostream>
#include "../../headers/Model/servidorBuilder.h"
#include "../../headers/Vista/consola.h"
#include "../../headers/Model/logger.h"

#include "../../tests/baseDeDatosTest.cpp"
using namespace std;

int main(int argc, char *argv[]) {

	////////////////////////////////////////TESTS/////////////////////////////////////////

	//BASE DE DATOS TESTS

//	BaseDeDatosTest* bdt = new BaseDeDatosTest();
//	bdt->agregarUnUsuario("Martin","tincho");
//	delete bdt;

//	BaseDeDatosTest* bdt = new BaseDeDatosTest();
//	bdt->obtenerUnUsuario("martin");
//	delete bdt;



	//////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////MAIN EXECUTE///////////////////////////////////////

	crear_logger();
	Consola* consola = new Consola();
	
	consola->cargarPaginaCrearServidor();
	while(!consola->getTerminado()){

		consola->cargarPagina(0);
	}

	delete consola;
	cerrar_logger();

	/////////////////////////////////////////////////////////////////////////////////////

	return 0;

}


