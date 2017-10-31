/*
 * Autito.h
 *
 *  Created on: 14 oct. 2017
 *      Author: bigfatpancha
 */

#ifndef PEPAS_SRC_MODEL_JUEGO_AUTITO_H_
#define PEPAS_SRC_MODEL_JUEGO_AUTITO_H_

#include "posicion.h"
#include <string>

class Autito {
private:
	Posicion *pos;
	float velocidad;
	int id;
	
	int desplazamientoEnX;
	int distanciaRecorrida;

public:
	Autito(Posicion *posInicial, int id);
	Autito(int dx, int dr, int id);

	Posicion *getPosicion();
	float getVelocidad();
	int getId();
	
	int getDesplazamientoEnX();
	int getDistanciaRecorrida();

	void setPosicion(Posicion *pos);
	void setVelocidad(float velocidad);
	
	void setDesplazamientoEnX(int dx);
	void setDistanciaRecorrida(int dr);

	virtual ~Autito();
};

#endif /* PEPAS_SRC_MODEL_JUEGO_AUTITO_H_ */
