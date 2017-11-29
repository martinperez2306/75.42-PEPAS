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

#define LEFT_MARGIN 115
#define RIGHT_MARGIN 700



Auto::Auto(int player)
{
	//Initialize the offsets
	//PosX =SCREEN_WIDTH/2 -100;
	PosY = SCREEN_HEIGHT - 180 ;
	ultPosY = 0 ;
	//Initialize the velocity
	VelX = 0;
	VelY = 0;
	posicion = 0;
    ultPosY = 0 ;
	PressUP = false;
    PressDown = false;
    Colision = false;
    frontColision = false,
    PressLeft_lock = false;
    PressRight_lock = false;
    PressUp_lock = false;
	this->jugador = player;
    destrozo = 0;
	this->scoreEtapa1 = 0;
	this->scoreEtapa2 = 0;
	this->scoreEtapa3 = 0;
	this->etapa = 1;


	this->setPosInicialDelAuto();

    RIGHT_BORDER = PosX + CAR_WIDTH;
    LEFT_BORDER = PosX;
}

int Auto::getX() {
	return PosX;
}


int Auto::getY() {
	return PosY;
}

int Auto::getUltPosY() {
	return ultPosY;
}

void Auto::setUltPosY(int posY) {
	this->ultPosY = posY;
}

void Auto::moveLeft_KD(int curve) {
	if (!PressLeft_lock) {
        VelX -= CAR_VEL_X;
        checkCurve(curve);
        lastMove = "left";
    }
}

void Auto::moveLeft_KU(int curve) {
    VelX += CAR_VEL_X;
    checkCurve(curve);
}

void Auto::moveRight_KD(int curve) {
    if (!PressRight_lock) {
        VelX += CAR_VEL_X;
        checkCurve(curve);
        lastMove = "right";
    }
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

    /*Si me voy de la pista*/
    if (PosX<= LEFT_MARGIN || PosX >= RIGHT_MARGIN)
        VEL_MAX = 25;
    else VEL_MAX = 50;

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

	if (PressUP && VelY < VEL_MAX && !frontColision) { //&& !Colision
		VelY += CAR_VEL;
	}

    if (PressDown && VelY < VEL_MAX && VelY > 0){
        VelY -= DESACELERAR;
    }

	posicion += VelY;

    RIGHT_BORDER = PosX + CAR_WIDTH;
    LEFT_BORDER = PosX;

    string datos = procesarMovimiento();

    return datos;


}

void Auto::moveUP_KD(int pos,int curve) {
    if (!PressUp_lock){
        PressUP = true;
        VelY += CAR_VEL;
        if (VelY>VEL_MAX)
            VelY = VEL_MAX;

        posicion = pos;
        lastMove = "up";
    }

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


string Auto::procesarMovimiento() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string posY = to_string(posicion);
    string posX = to_string(PosX);
    string velY = to_string(VelY);
    stringACrear = separador + "20" + separador + posY + separador + posX + separador + velY + separador ;
    return stringACrear;
}

int Auto::obtenerPlayer() {
	return jugador;
}

void Auto::setJugador(int i) {
	this->jugador = i;

}


void Auto::estaEnColision(string lastMove, float velY) {
        cout<<"recibi el lastmove: "<<lastMove<<endl;
        if (lastMove == "up"  || velY > VEL_MIN) {
            VelY = VEL_MIN;
            PressUp_lock = true;
            frontColision = true;
            PressRight_lock = false;
            PressLeft_lock = false;
           // cout<<"11111111111"<<endl;
        } /*else if (velY == VEL_MIN && lastMove == "left")
            PressLeft_lock = true;
        else if (velY == VEL_MIN && lastMove == "right")
            PressRight_lock = true;
*/
        if (lastMove == "left" && !frontColision) {
            PosX -= VelX;
            PressLeft_lock = true;
           // cout<<"2222222222"<<endl;
        }
        if (lastMove == "right" && !frontColision) {
            PosX -= VelX;
            PressRight_lock = true;
           // cout<<"33333333333"<<endl;
    }
}

string Auto::getLastMove() {
    return lastMove;
}

float Auto::getVelY() {
    return VelY;
}

void Auto::noEstaEnColision() {
    PressLeft_lock = false;
    PressRight_lock = false;
    PressUp_lock = false;
    frontColision = false;
}

void Auto::setPosInicialDelAuto(){

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

void Auto::agregarDestrozo() {
    destrozo++;
}

int Auto::obtenerDestrozo(){
    return destrozo;
}


void Auto::setScoreEtapa1(int score) {
    this->scoreEtapa1 += score;
}

void Auto::setScoreEtapa2(int score) {
    this->scoreEtapa2 += score;
}

void Auto::setScoreEtapa3(int score) {
    this->scoreEtapa3 += score;
}

int Auto::getEtapa() {
    return this->etapa;
}

void Auto::incrementarEtapa() {
    this->etapa += 1;
}



int Auto::getScoreEtapa1() {
    return this->scoreEtapa1;
}

void Auto::frenarAuto() {
    VelY = VEL_MIN;
}

void Auto::lockearTeclas() {
    PressLeft_lock = true;
    PressRight_lock = true;
    PressUp_lock = true;
    frontColision = true;
}




