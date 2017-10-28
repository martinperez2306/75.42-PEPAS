#include "../../headers/Model/puntero.h"

Puntero::Puntero(){
	this->angulo = 0;
	this->distanciaRecorrida = 0;
}

void Puntero::setDistancia(int distancia){
	this->distanciaRecorrida = distancia;
}

int Puntero::getDistancia(){
	return this->distanciaRecorrida;
}

void Puntero::setAngulo(int angulo){
	this->angulo = angulo;
}

int Puntero::getAngulo(){
	return this->angulo;
}

void Puntero::girarDerecha(){
	this->angulo = this->angulo - 45;
	this->unificarAngulo();
}

void Puntero::girarIzquierda(){
	this->angulo = this->angulo + 45;
	this->unificarAngulo();
}

void Puntero::unificarAngulo(){
	if(this->angulo < 0){
		this->angulo+= 360;
	}
	else if (this->angulo >= 360){
		this->angulo -= 360;
	}
}

Posicion* Puntero::avanzar(Posicion* posicion,int distancia){

	Posicion* posFinal = new Posicion(posicion->getX(),posicion->getY());
	int inicio = 0;
	while(inicio < distancia){
	switch(this->angulo){

	case 0:
		posFinal->setX(posFinal->getX() + 1);
		break;
	case 45:
		posFinal->setX(posFinal->getX() + 1);
		posFinal->setY(posFinal->getY() - 1);
		break;
	case 90:
		posFinal->setY(posFinal->getY() - 1);
		break;
	case 135:
		posFinal->setX(posFinal->getX() - 1);
		posFinal->setY(posFinal->getY() - 1);
		break;
	case 180:
		posFinal->setX(posFinal->getX() - 1);
		break;
	case 225:
		posFinal->setX(posFinal->getX() - 1);
		posFinal->setY(posFinal->getY() + 1);
		break;
	case 270:
		posFinal->setY(posFinal->getY() + 1);
		break;
	case 315:
		posFinal->setX(posFinal->getX() + 1);
		posFinal->setY(posFinal->getY() + 1);
		break;
	}
	inicio ++;
	}
	return posFinal;
}

Puntero::~Puntero(){

}

