/*
 * Autito.h
 *
 *  Created on: 14 oct. 2017
 *      Author: bigfatpancha
 */

#ifndef PEPAS_SRC_MODEL_JUEGO_AUTITO_H_
#define PEPAS_SRC_MODEL_JUEGO_AUTITO_H_

#include <iostream>
using namespace std;

class Auto {

private:

	float PosX, PosY, posicion;
	float VelX, VelY;
	bool PressUP, curveR, curveL, conectado;
	int jugador;

public:

	static const int CAR_WIDTH = 200;
	static const int CAR_HEIGHT = 103;

	float CAR_VEL = 0.2;
	float CAR_VEL_X =  0.5;
	float DESACELERAR = 0.1;
	float DESVIO = 0.3; // desvio en curvas
	int VEL_MAX = 50;
	int VEL_MIN = 0;


	Auto(int jugador);

	int getX();

	int getY();

	void moveLeft_KD(int curve);

	void moveRight_KD(int curve);

	void moveLeft_KU(int curve);

	void moveRight_KU(int curve);

	void moveUP_KD(int pos,int curve);

	void moveDown_KD(int pos,int curve);

	void moveUP_KU(int pos,int curve);

	void moveDown_KU(int pos,int curve);

	string calculateMove(int curve);

	float getPosition();

	bool isMoving();

	void checkCurve(int curve);

	string procesarMovimiento();

	string agregarPadding(int lenght);

	int obtenerPlayer();

	bool isConectado();

	void desconectar();
};


#endif /* PEPAS_SRC_MODEL_JUEGO_AUTITO_H_ */
