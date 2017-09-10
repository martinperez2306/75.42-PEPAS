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
	int destinatario;
	int codigo;

	bool isBroadcast();

public:
	// TODO definir los codigos para cada tipo de mensaje
	static const int BROADCAST_MSG = 0;
	static const int PRIVATE_MSG = 0;

	static const int BROADCAST = 0;
	Mensaje();
	Mensaje(int codigo, string texto, int destinatario);
	string getTexto();
	int getDestinatario();
	string toSrvText();
	virtual ~Mensaje();
};

} /* namespace std */

#endif /* COM_PEPAS_MODEL_MENSAJE_H_ */
