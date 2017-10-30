#include "../../headers/Model/segmento.h"

Segmento::Segmento(){
	this->posicionFinal= NULL;
	this->posicionInicial= NULL;
	this->longitud = 0;
	this->curva = 0;
}

Segmento::Segmento(Posicion* posInicial,Posicion* posFinal){
	this->posicionFinal = posFinal;
	this->posicionInicial = posInicial;
	this->longitud = 0;
	this->curva = 0;
}

void Segmento::setPosicionFinal(Posicion* posicionFinal){
	this->posicionFinal = posicionFinal;
}

void Segmento::setPosicionInicial(Posicion* posicionInicial){
	this->posicionInicial = posicionInicial;
}

void Segmento::setLongitud(int longitud){
	this->longitud = longitud;
}

void Segmento::setCurva(int curva){
	this->curva = curva;
}

Posicion* Segmento::getPosicionFinal(){
	return this->posicionFinal;
}

Posicion* Segmento::getPosicionInicial(){
	return this->posicionInicial;
}

int Segmento::getLongitud(){
	return this->longitud;
}

int Segmento::getCurva(){
	return this->curva;
}

Segmento::~Segmento(){
	delete this->posicionFinal;
	delete this->posicionInicial;
}


