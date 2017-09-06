/*
 * ClienteParser.cpp
 *
 *  Created on: 3 sep. 2017
 *      Author: bigfatpancha
 */
#include "../../headers/com.pepas.parser/ClienteParser.h"

//SERVIDOR BUILDER

//BASE DE DATOS Y SERVIDOR SON PEDIDOS EN MEMORIA ACA. DEBEN SER LIBERADAS EN EL CONTROLLER (EL SERVIDOR) Y LA BASE DE DATOS (POR EL SERVIDOR)
ClienteParser::ClienteParser(){}

void ClienteParser::parsearXML(char* xmlPath){
	struct sockaddr_in sa;
	char str[15];
	pugi::xml_document documento;
	pugi::xml_parse_result result = documento.load_file(xmlPath);
	cout << "Load Result: " << result.description() <<endl;

	//PARSING XML (EL COMPILADOR PODRIA DECIR QUE NO ANDA PERO SI ANDA WACHOS)
	pugi::xml_node nodeIp = documento.child("cliente").child("conexion").child("IP");
	const char* ip = nodeIp.text().as_string();
	if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == -1) {
		// TODO logear error
		// TODO levantar archivo default
	}


	pugi::xml_node nodePuerto = documento.child("cliente").child("conexion").child("puerto");
	int puerto = nodePuerto.text().as_int();

	//TODO levantar archivo de test

	//BUILDING SERVICE

	inet_ntop(AF_INET, &(sa.sin_addr), str, 15);

	cout << "IP: " << str <<endl;
	cout << "Puerto: " << puerto <<endl;
	this->ip = str;
	this->puerto = puerto;
}

