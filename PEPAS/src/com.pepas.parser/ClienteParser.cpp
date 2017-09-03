/*
 * ClienteParser.cpp
 *
 *  Created on: 3 sep. 2017
 *      Author: bigfatpancha
 */
#include "ClienteParser.h"
#include <arpa/inet.h>

//SERVIDOR BUILDER

//BASE DE DATOS Y SERVIDOR SON PEDIDOS EN MEMORIA ACA. DEBEN SER LIBERADAS EN EL CONTROLLER (EL SERVIDOR) Y LA BASE DE DATOS (POR EL SERVIDOR)
ClienteParser::ClienteParser(){}

sockaddr ClienteParser::getSocketAddr(){
	return this->socketAddr;
}


void ClienteParser::parsearXML(){
	struct sockaddr_in sa;
	pugi::xml_document documento;
	pugi::xml_parse_result result = documento.load_file("C:/Users/martin/workspaceCpp/Hello World/src/server.xml");
	cout << "Load Result: " << result.description() <<endl;

	//PARSING XML (EL COMPILADOR PODRIA DECIR QUE NO ANDA PERO SI ANDA WACHOS)
	pugi::xml_node nodeIp = documento.child("cliente").child("conexion").child("IP");
	char* ip = nodeIp.text();
	if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == -1) {
		// TODO logear error
		// TODO levantar archivo default
	}

	pugi::xml_node nodePuerto = documento.child("servidor").child("cliente").child("conexion").child("puerto");
	sa.sin_port = nodePuerto.text();

	//TODO levantar archivo de test

	//BUILDING SERVICE
	this->socketAddr = sa;
}

