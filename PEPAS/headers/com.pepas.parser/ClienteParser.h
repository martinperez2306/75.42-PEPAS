/*
 * ClienteParser.h
 *
 *  Created on: 3 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_PARSER_CLIENTEPARSER_H_
#define COM_PEPAS_PARSER_CLIENTEPARSER_H_

#include "../pugi/pugixml.hpp"
#include "../../headers/com.pepas.logger/Logger.h"
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class ClienteParser{

public:

	struct SocketData {
		char* ip;
		int puerto;
		char *rutaFile;
	};
	ClienteParser();

	ClienteParser::SocketData parsearXML(char* xmlPath);
	bool puertoValido(int puerto);
	bool pathValido(const char* path);

		//no libera la memoria del servidor. Recordar Eliminarla en el programa principal.
	~ClienteParser();
};

#endif /* COM_PEPAS_PARSER_CLIENTEPARSER_H_ */
