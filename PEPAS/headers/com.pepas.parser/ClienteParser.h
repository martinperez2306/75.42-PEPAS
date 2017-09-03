/*
 * ClienteParser.h
 *
 *  Created on: 3 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_PARSER_CLIENTEPARSER_H_
#define COM_PEPAS_PARSER_CLIENTEPARSER_H_

#include "pugixml.hpp"
#include <iostream>
#include <string>

using namespace std;

class ClienteParser{

private:
	struct sockaddr_in socketAddr;

public:
	ClienteParser();

	sockaddr getSocketAddr();

	void parsearXML();

	//no libera la memoria del servidor. Recordar Eliminarla en el programa principal.
	~ClienteParser();
};

#endif /* COM_PEPAS_PARSER_CLIENTEPARSER_H_ */
