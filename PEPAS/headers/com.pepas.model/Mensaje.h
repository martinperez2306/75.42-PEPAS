/*
 * Mensaje.h
 *
 *  Created on: 9 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_MODEL_MENSAJE_H_
#define COM_PEPAS_MODEL_MENSAJE_H_

#include <iostream>
#include <string>

namespace std {

class Mensaje {
private:
	string texto;
	string destinatario;
	string emisor;
	int codigo;


public:
	// TODO definir los codigos para cada tipo de mensaje
	static const int BROADCAST_MSG = 2;
	static const int PRIVATE_MSG = 3;


	Mensaje(int codigo, string texto, string emisor, string receptor);
	string obtenerTexto();
	string obtenerDestinatario();
	string obtenerEmisor();;
	int obtenerCodigo();
	virtual ~Mensaje();
};

} /* namespace std */

#endif /* COM_PEPAS_MODEL_MENSAJE_H_ */
