#include "../../headers/com.pepas.model/segmento.h"

Segmento::Segmento(){
	this->posicionFinal= NULL;
	this->posicionInicial= NULL;
	this->curva = 0;
	this->longitud = 0;
}

Segmento::Segmento(Posicion* posInicial,Posicion* posFinal){
	this->posicionFinal = posFinal;
	this->posicionInicial = posInicial;
}

Posicion* Segmento::getPosicionFinal(){
	return this->posicionFinal;
}

Posicion* Segmento::getPosicionInicial(){
	return this->posicionInicial;
}

int Segmento::getCurva(){
	return this->curva;
}

int Segmento::getLongitud(){
	return this->longitud;
}

void Segmento::setCurva(int curva){
	this->curva = curva;
}

void Segmento::setLongitud(int longitud){
	this->longitud = longitud;
}

Segmento::~Segmento(){
	delete this->posicionFinal;
	delete this->posicionInicial;
}


