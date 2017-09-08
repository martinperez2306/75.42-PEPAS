#include <iostream>
#include "../headers/com.pepas.parser/ClienteParser.h"
#include "../headers/com.pepas.controllers/clienteController.h"
#include "../headers/com.pepas.view/consola.h"
using namespace std;


int main(int argc, char *argv[]) {

	Consola* consola = new Consola();
	consola->cargarPagina();



	/*ClienteParser *clienteParser = new ClienteParser();
	//char* xmlPath = argv[0];
	char* xmlPath = "cliente.xml";
	clienteParser->parsearXML(xmlPath);

	ClienteController* clienteController = new ClienteController(clienteParser);
	clienteController->conectarConElServidor();
	*/

}




