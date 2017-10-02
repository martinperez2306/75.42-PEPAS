#include <iostream>


#include "../headers/com.pepas.parser/ClienteParser.h"
#include "../headers/com.pepas.controllers/clienteController.h"
#include "../headers/com.pepas.view/consola.h"
#include "../headers/com.pepas.logger/Logger.h"
using namespace std;



int main(int argc, char *argv[]) {
	crear_logger();
	Consola *consola = new Consola();
	consola->cargarMenuPrincipal();
	cerrar_logger();
	

}




