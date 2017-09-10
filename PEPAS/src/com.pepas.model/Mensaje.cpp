/*
 * Mensaje.cpp
 *
 *  Created on: 9 sep. 2017
 *      Author: bigfatpancha
 */

#include "../../headers/com.pepas.model/Mensaje.h"

namespace std {

Mensaje::Mensaje() {
	// TODO Auto-generated constructor stub

}

Mensaje::Mensaje(int codigo, string texto, int destinatario) {
	this->codigo = codigo;
	this->texto = texto;
	this->destinatario = destinatario;

}

string Mensaje::toSrvText() {
	string mensaje = "";
	mensaje += this->codigo; // TODO definir los codigos para cada mensaje
	mensaje += this->destinatario; // TODO definir un largo para mandar el numero
	mensaje += this->texto.length(); // TODO definir un largo para mandar el numero
	mensaje += this->texto;

}

bool Mensaje::isBroadcast() {
	return this->destinatario == 0;
}

Mensaje::~Mensaje() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
