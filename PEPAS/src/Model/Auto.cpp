/*
 * Autito.cpp
 *
 *  Created on: 14 oct. 2017
 *      Author: bigfatpancha
 */

#include "../../headers/Model/Auto.h"

//
// Created by arturi on 25/10/17.
//
#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024



Auto::Auto(int player)
{
	//Initialize the offsets
	//PosX =SCREEN_WIDTH/2 -100;
	PosY = SCREEN_HEIGHT - 180 ;
	//Initialize the velocity
	VelX = 0;
	VelY = 0;
	posicion = 0;
	PressUP = false;
    PressDown = false;
	this->jugador = player;

	switch (jugador){
		case 1:{
			PosX = 230;
			posicion = 400;
		}break;
		case 2:{
			PosX =550;
			posicion = 400;
		}break;
		case 3:{
			PosX = 230;

		}
            break;
		case 4:{
			PosX = 550;
		}
			break;

	}
}

int Auto::getX() {
	return PosX;
}


int Auto::getY() {
	return PosY;
}


void Auto::moveLeft_KD(int curve) {
	VelX -= CAR_VEL_X;
    checkCurve(curve);

}

void Auto::moveLeft_KU(int curve) {
    VelX += CAR_VEL_X;
    checkCurve(curve);
}

void Auto::moveRight_KD(int curve) {
	VelX += CAR_VEL_X ;
    checkCurve(curve);
}

void Auto::moveRight_KU(int curve) {
	VelX -= CAR_VEL_X;
    checkCurve(curve);
}

string Auto::calculateMove(int curve) {

	//cout <<"posY "<<posicion<<endl;
	//cout <<"velY "<<VelY<<endl;
	// cout <<"posx "<<PosX<<endl;
	//cout <<"velX "<<VelX<<endl;
    //checkCurve(posicion);
	checkCurve(curve);
	PosX += VelX;

	if (VelY >= VEL_MAX/2 && curveL && PosX < SCREEN_WIDTH - CAR_WIDTH){
		PosX += DESVIO;
	}else if (VelY >= VEL_MAX/2 && curveR && PosX > 0){
		PosX -= DESVIO;

	}
	else if( ( PosX < 0 ) || ( PosX + CAR_WIDTH > SCREEN_WIDTH ) )
	{
		//Move back
		PosX -= VelX;
	}

	/*No excedo la velocidad maxima*/
	if (VelY > VEL_MAX)
		VelY = VEL_MAX;
	else if (VelY < VEL_MIN )
		VelY = VEL_MIN;

	/*Desacelera automaticamente*/
	if (VelY>VEL_MIN && VelY < VEL_MAX && !PressUP) {
		VelY -= DESACELERAR;

	}
	/*Evito que salga de la pantalla*/
	if( ( PosY < 0 ) || ( PosY + CAR_HEIGHT > SCREEN_HEIGHT ) )
	{
		posicion -= VelY;
	}

	if (PressUP && VelY < VEL_MAX) {
		VelY += CAR_VEL;
	}

    if (PressDown && VelY < VEL_MAX && VelY > 0){
        VelY -= DESACELERAR;
    }

	posicion += VelY;

    string datos = procesarMovimiento();

    return datos;


}

void Auto::moveUP_KD(int pos,int curve) {
	PressUP = true;
	VelY += CAR_VEL;
	if (VelY>VEL_MAX){
		VelY = VEL_MAX;
	}
	posicion = pos;
//    checkCurve(curve);
}

void Auto::moveDown_KD(int pos,int curve) {
    PressDown = true;
	VelY -= CAR_VEL;
	if (VelY < VEL_MIN)
		VelY = VEL_MIN;
	posicion = pos;
//    checkCurve(curve);
}

void Auto::moveUP_KU(int pos,int curve) {
	PressUP = false;
	VelY -= CAR_VEL;
	posicion = pos;
//    checkCurve(curve);

}

void Auto::moveDown_KU(int pos,int curve) {
    PressDown = false;
	VelY -= CAR_VEL;
	posicion = pos;
//    checkCurve(curve);

}

float Auto::getPosition() {
	return posicion;
}

bool Auto::isMoving() {
	bool move;
	if (VelY>0)
		move = true;
	else move = false;
	return move ;
}

void Auto::checkCurve(int curve) {

    if (curve < 0){ //curva a la derecha
        curveR = true;
        curveL = false;
    }
    if (curve > 0) { //curva a la izquierda
        curveL = true;
        curveR = false;
    }
    if(curve == 0){
        curveR = false;
        curveL = false;
    }

}

string Auto::agregarPadding(int lenght) {
    string mensajeProcesado;
    string largo = to_string(lenght);
    if (lenght < 10)
        mensajeProcesado = "000" + largo;
    else if (lenght < 100)
        mensajeProcesado = "00" + largo;
    else if (lenght < 1000)
        mensajeProcesado = "0" + largo;
    else mensajeProcesado = largo;
    return mensajeProcesado;
}

string Auto::procesarMovimiento() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string posY = to_string(posicion);
    string posX = to_string(PosX);
    stringACrear = separador + "20" + separador + posY + separador + posX + separador;
    return stringACrear;
}

int Auto::obtenerPlayer() {
	return jugador;
}

void Auto::setJugador(int i) {
	this->jugador = i;

}
