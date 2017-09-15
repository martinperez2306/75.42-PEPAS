/*
 * ClienteParser.cpp
 *
 *  Created on: 3 sep. 2017
 *      Author: bigfatpancha
 */
#include "../../headers/com.pepas.parser/ClienteParser.h"

//SERVIDOR BUILDER

//BASE DE DATOS Y SERVIDOR SON PEDIDOS EN MEMORIA ACA. DEBEN SER LIBERADAS EN EL CONTROLLER (EL SERVIDOR) Y LA BASE DE DATOS (POR EL SERVIDOR)
ClienteParser::ClienteParser(){
}

ClienteParser::SocketData ClienteParser::parsearXML(char* xmlPath) {
	struct sockaddr_in sa;
	ClienteParser::SocketData sd;
	char str[15];
	pugi::xml_document documento;
	pugi::xml_parse_result result = documento.load_file(xmlPath);
	cout << "Load Result: " << result.status << endl;
	if(result.status == 0) {
		//PARSING XML (EL COMPILADOR PODRIA DECIR QUE NO ANDA PERO SI ANDA WACHOS)
		pugi::xml_node nodeIp = documento.child("cliente").child("conexion").child("IP");
		const char *ip = nodeIp.text().as_string();
		if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == -1) {
			return ClienteParser::parsearXML("clienteDefault.xml");
		}
		pugi::xml_node nodePuerto = documento.child("cliente").child("conexion").child("puerto");
		int puerto = nodePuerto.text().as_int();
		if(!puertoValido(puerto)) {
			return ClienteParser::parsearXML("clienteDefault.xml");
		}
		pugi::xml_node nodeTestfile = documento.child("cliente").child("testfile");
		const char* testFile = nodeTestfile.text().as_string();
		if(!pathValido(testFile)) {
			return ClienteParser::parsearXML("clienteDefault.xml");
		}

		inet_ntop(AF_INET, &(sa.sin_addr), sd.ip, 15);
		sd.puerto = puerto;
		return sd;
	} else {
		return ClienteParser::parsearXML("clienteDefault.xml");
	}
}

bool ClienteParser::puertoValido(int puerto) {
	return true;
}

bool ClienteParser::pathValido(const char* path) {
	return true; 
}
