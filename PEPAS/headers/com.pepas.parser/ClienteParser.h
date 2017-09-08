/*
 * ClienteParser.h
 *
 *  Created on: 3 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_PARSER_CLIENTEPARSER_H_
#define COM_PEPAS_PARSER_CLIENTEPARSER_H_

#include "../pugi/pugixml.hpp"
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class ClienteParser{

private:
	char *ip;
	int puerto;

public:
	ClienteParser();

	const char* getIp();
	int getPuerto();

	void parsearXML(char* xmlPath);

		//no libera la memoria del servidor. Recordar Eliminarla en el programa principal.
	~ClienteParser();
};

#endif /* COM_PEPAS_PARSER_CLIENTEPARSER_H_ */
