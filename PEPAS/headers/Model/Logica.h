/*
 * Logica.h
 *
 *  Created on: 14 oct. 2017
 *      Author: bigfatpancha
 */

#ifndef PEPAS_SRC_MODEL_JUEGO_LOGICA_H_
#define PEPAS_SRC_MODEL_JUEGO_LOGICA_H_



#include "posicion.h"
#include "Autito.h"
#include <algorithm>
#include <list>
#include "segmento.h"

using namespace std;

class Logica {

private:
	bool isRutaRecta(int distancia);
	bool isCurvaDerecha(Posicion *pos);
	int incrementar(int posicionY, float incremento, int distanciaTotal);
	float acelerar(float velocidad, float aceleracion, float deltaTiempo);
	float limitarVelocidad(float velocidad, float minimo, float maximo);

	int FIN_DE_RUTA = -1;
	int ACTUALIZADO = 1;

	char const ARRIBA = 'A';
	char const ABAJO = 'B';
	char const DERECHA = 'D';
	char const IZQUIERDA = 'I';

	float const VELOCIDAD_MAXIMA = 200;
	float const VELOCIDAD_ACELERACION = VELOCIDAD_MAXIMA / 5;
	float const VELOCIDAD_FRENADO = -VELOCIDAD_MAXIMA;
	float const VELOCIDAD_DESACELERACION = -VELOCIDAD_MAXIMA / 5;

	int const CURVA = 2;
	float const FUERZA_CENTRIFUGA = 0.3;

	int largoPista;
	list<Segmento*>* ruta;

public:
	Logica(int largoPista);

	void setRuta(list<Segmento*>* ruta);

	int actualizar(Autito *autito, char comando, float deltaTiempo);

	virtual ~Logica();
};

#endif /* PEPAS_SRC_MODEL_JUEGO_LOGICA_H_ */
