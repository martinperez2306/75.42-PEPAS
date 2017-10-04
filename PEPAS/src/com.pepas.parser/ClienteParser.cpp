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

ClienteParser::SocketData ClienteParser::parsearXML(const char* xmlPath) {
	ClienteParser::SocketData sd;
	pugi::xml_document documento;
	pugi::xml_parse_result result = documento.load_file(xmlPath, pugi::parse_default|pugi::parse_declaration);
	cout << "Load Result: " << result.description() <<endl;
	if(result.status == 0) {
		//PARSING XML (EL COMPILADOR PODRIA DECIR QUE NO ANDA PERO SI ANDA WACHOS)
		pugi::xml_node nodeIp = documento.child("cliente").child("conexion").child("IP");
		const char *ip = nodeIp.text().as_string();
		if(!validarIp(ip)) {
			//return ClienteParser::parsearXML("clienteDefault.xml");
            return ClienteParser::parsearXML("clienteDefault.xml");
		}
		pugi::xml_node nodePuerto = documento.child("cliente").child("conexion").child("puerto");
		const char* puerto = nodePuerto.text().as_string();
		if(!puertoValido(puerto)) {
			//return ClienteParser::parsearXML("clienteDefault.xml");
            return ClienteParser::parsearXML("clienteDefault.xml");
		}
		pugi::xml_node nodeTestfile = documento.child("cliente").child("testfile").child("path");
		const char* testFile = nodeTestfile.text().as_string();
		if(!pathValido(testFile)) {
			//return ClienteParser::parsearXML("clienteDefault.xml");
            return ClienteParser::parsearXML("clienteDefault.xml");
		}
		sd.ip = ip;
		sd.puerto = atoi(puerto);
		sd.rutafile = testFile;
	
		return sd;
	} else {
		//return ClienteParser::parsearXML("clienteDefault.xml");
        return ClienteParser::parsearXML("clienteDefault.xml");
	}
}

bool ClienteParser::validarIp(const char *ip){
	unsigned char buf[sizeof(struct in6_addr)];
	int ipValida = inet_pton(AF_INET, ip, buf);
	if (ipValida == 0){
		return false;
	}
	return true;
}

bool ClienteParser::puertoValido(const char* puertoTxt) {
	if(sonDigitos(puertoTxt)) {
		int puerto = atoi(puertoTxt);
		return puerto > 0 && puerto < 65535;
	} else {
		cout<<"Puerto invalido"<<endl;
		return false;
	}
}

bool ClienteParser::sonDigitos(const char* str){
	for (unsigned int i = 0; i < strlen (str); i++) {
		if (! isdigit (str[i])) {
			return false;
		}
	}
	return true;
}

bool ClienteParser::pathValido(const char* path) {
	std::ifstream test(path);
	return !!test;
//	return true;
}



