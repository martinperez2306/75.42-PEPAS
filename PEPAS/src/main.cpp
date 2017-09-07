#include <iostream>
#include "../headers/com.pepas.parser/ClienteParser.h"
#include "../headers/com.pepas.controllers/clienteController.h"
using namespace std;


int main(int argc, char *argv[]) {

	ClienteParser *clienteParser = new ClienteParser();
	//char* xmlPath = argv[0];
	char* xmlPath = "cliente.xml";
	clienteParser->parsearXML(xmlPath);

	ClienteController* clienteController = new ClienteController(clienteParser);
	clienteController->conectarConElServidor();

}


