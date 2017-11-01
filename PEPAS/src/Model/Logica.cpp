/*
 * Logica.cpp
 *
 *  Created on: 14 oct. 2017
 *      Author: bigfatpancha
 */

#include "../../headers/Model/Logica.h"

Logica::Logica(int largoPista) {
	this->largoPista = largoPista;
}

bool Logica::isRutaRecta(int distancia) {
	list<Segmento*>* ruta = this->ruta;
	int acumLongitud = 0;
	for(list<Segmento*>::iterator it = ruta->begin(); it != ruta->end();++it){
		Segmento* seg = *it;
		acumLongitud += seg->getLongitud();
		if(acumLongitud == distancia) {
			return false;
		}
	}
	return true;
}

int Logica::incrementar(int posY, float incremento, int distanciaTotal) {
	float result = posY + incremento;
		while (result >= distanciaTotal)
			result -= distanciaTotal;
		while (result < 0)
			result += distanciaTotal;
	return result;
}

float Logica::acelerar(float velocidad, float aceleracion, float deltaTiempo) {
	return velocidad + (aceleracion * deltaTiempo);
}

float Logica::limitarVelocidad(float velocidad, float minimo, float maximo) {
	return (std::max)(minimo, (std::min)(velocidad, maximo));
}

int Logica::actualizar(Autito *autito, char comando, float deltaTiempo) {

	float porcentajeVelocidad = autito->getVelocidad() / VELOCIDAD_MAXIMA;
	float desplazamientoX = deltaTiempo * 2 * porcentajeVelocidad;

	int dr = autito->getDistanciaRecorrida();
	dr = incrementar(dr, deltaTiempo * autito->getVelocidad(), this->largoPista);

	autito->setDistanciaRecorrida(dr);
	// TODO calcular offset del cielo
	// TODO calcular offset del arbol

	int posX = autito->getDesplazamientoEnX();
	if(IZQUIERDA == comando)
		posX = posX - desplazamientoX;

	if(DERECHA == comando)
		posX = posX + desplazamientoX;

	int factorCurva = CURVA;
	if(isRutaRecta(autito->getDistanciaRecorrida()))
		factorCurva = 1;

	posX = posX - (desplazamientoX * porcentajeVelocidad * factorCurva * FUERZA_CENTRIFUGA);

	autito->setDesplazamientoEnX(posX);

	float velocidad = autito->getVelocidad();
	if(ARRIBA == comando)
		velocidad = acelerar(velocidad, VELOCIDAD_ACELERACION, deltaTiempo);
	else if(ABAJO == comando)
		velocidad = acelerar(velocidad, VELOCIDAD_FRENADO, deltaTiempo);
	else
		velocidad = acelerar(velocidad, VELOCIDAD_DESACELERACION, deltaTiempo);

	velocidad = limitarVelocidad(velocidad, 0, VELOCIDAD_MAXIMA);

	autito->setVelocidad(velocidad);

	return ACTUALIZADO;

}

void Logica::setRuta(list<Segmento*>* ruta) {
	this->ruta = ruta;
}

Logica::~Logica() {}

