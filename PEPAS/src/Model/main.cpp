#include <iostream>
#include "../../headers/Model/servidorBuilder.h"
#include "../../headers/Vista/consola.h"
#include "../../headers/Model/logger.h"


//#include "../../tests/baseDeDatosTest.cpp"
#include "../../tests/threadsTests.cpp"
#include <cstdlib>
#include <pthread.h>
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


	//THREADS TESTS
//	pthread_t thread;
//	pthread_t thread2;
//	cout<<"creando thread 1"<<endl;
//	pthread_create(&thread,NULL,PrintHello,NULL);
//	cout<<"creadno thread 2"<<endl;
//	pthread_create(&thread2,NULL,PrintHello,NULL);
//	ThreadsTests test;
//	test.crearUnNuevoThreadYCerrarloLuegoDeMain();
//	Thread::terminar();

	//////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////MAIN EXECUTE///////////////////////////////////////

	crear_logger();
	Consola* consola = new Consola();

	consola->cargarPaginaCrearServidor();
	while(!consola->getTerminado()){
		//consola->abrirServidorAClientes();
		consola->cargarPagina(0);
	}

	delete consola;
	cerrar_logger();

	/////////////////////////////////////////////////////////////////////////////////////

	return 0;

}


