#include <iostream>
#include "../headers/com.pepas.parser/ClienteParser.h"
using namespace std;


int main(int argc, char *argv[]) {

	ClienteParser *clienteParser = new ClienteParser();
	//char* xmlPath = argv[0];
	char* xmlPath = "/home/bigfatpancha/Documentos/tpTaller/primeraParte/75.42-PEPAS/PEPAS/src/cliente.xml";
	clienteParser->parsearXML(xmlPath);
}


