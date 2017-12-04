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


	float PosX, PosY,ultPosY, posicion, RIGHT_BORDER, LEFT_BORDER;


	float VelX, VelY;
	bool PressUP, PressDown, PressLeft_lock, PressRight_lock, PressUp_lock, curveR, curveL, frontColision, Colision,rightColision,leftColision,PressR,PressL;
	int jugador, destrozo;
	string lastMove;

	int scoreEtapa1, scoreEtapa2, scoreEtapa3, etapa;

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

	int getUltPosY();

	void setUltPosY(int posY);

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



	void checkCurve(int curve);

	string procesarMovimiento();



	string getLastMove();

	int obtenerPlayer();

	void setJugador(int i);

	void estaEnColision(string move, float velY);

    float getVelY();

    void noEstaEnColision();

    void setPosInicialDelAuto();



	void agregarDestrozo();

	int obtenerDestrozo();


	void setScoreEtapa1(int score);
	void setScoreEtapa2(int score);
	void setScoreEtapa3(int score);


	void incrementarEtapa();
	int getEtapa();
	int getScoreEtapa1();


    void frenarAuto();

    void lockearTeclas();

    int getScoreEtapa2();
    int getScoreEtapa3();
};


#endif /* PEPAS_SRC_MODEL_JUEGO_AUTITO_H_ */
