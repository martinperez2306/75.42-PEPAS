/*
 * Autito.cpp
 *
 *  Created on: 14 oct. 2017
 *      Author: bigfatpancha
 */

#include "../../headers/Model/Autito.h"

Autito::Autito(Posicion *posInicial, int id) {
	this->pos = posInicial;
	this->velocidad = 0;
	this->id = id;
}

Autito::Autito(int dx, int dr, int id) {
	this->desplazamientoEnX = dx;
	this->distanciaRecorrida = dr;
	this->id = id;
	this->velocidad = 0;
}

void Autito::setPosicion(Posicion *pos) {
	this->pos = pos;
}

void Autito::setVelocidad(float velocidad) {
	this->velocidad = velocidad;
}

Posicion *Autito::getPosicion() {
	return this->pos;
}

float Autito::getVelocidad() {
	return this->velocidad;
}
int Autito::getId() {
	return this->id;
}

void Autito::setDesplazamientoEnX(int dx) {
	this->desplazamientoEnX += dx;
}

void Autito::setDistanciaRecorrida(int dr) {
	this->distanciaRecorrida += dr;
}

int Autito::getDesplazamientoEnX() {
	return this->desplazamientoEnX;
}

int Autito::getDistanciaRecorrida() {
	return this->distanciaRecorrida;
}

Autito::~Autito() {

}

