#include <iostream>


#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.parser/ClienteParser.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.controllers/clienteController.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.view/consola.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.logger/Logger.h"
using namespace std;



int main(int argc, char *argv[]) {


	crear_logger();
	if(argc != 2){
		Consola *consola = new Consola("1");
		consola->cargarMenuPrincipal();
	}
	else{
		Consola *consola = new Consola(argv[1]);
		consola->cargarMenuPrincipal();
	}


	cerrar_logger();


}




