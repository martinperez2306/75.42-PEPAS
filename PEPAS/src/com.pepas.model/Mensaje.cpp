/*
 * Mensaje.cpp
 *
 *  Created on: 9 sep. 2017
 *      Author: bigfatpancha
 */

#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/Mensaje.h"

namespace std {



Mensaje::Mensaje(int codigo, string texto, string emisor, string receptor) {
	this->codigo = codigo;
	this->texto = texto;
	this->emisor = emisor;
	this->destinatario = receptor;

}

string Mensaje::obtenerEmisor() {
	return this->emisor;
}

string Mensaje::obtenerDestinatario() {
	return this->destinatario;
}

string Mensaje::obtenerTexto() {
	return this->texto;
}

Mensaje::~Mensaje() {
	// TODO Auto-generated destructor stub
}

int Mensaje::obtenerCodigo() {
	return this->codigo;
}


} /* namespace std */
