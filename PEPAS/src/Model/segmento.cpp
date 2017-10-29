#include "../../headers/Model/segmento.h"

Segmento::Segmento(){
	this->posicionFinal= NULL;
	this->posicionInicial= NULL;
}

Segmento::Segmento(Posicion* posInicial,Posicion* posFinal){
	this->posicionFinal = posFinal;
	this->posicionInicial = posInicial;
}

void Segmento::setPosicionFinal(Posicion* posicionFinal){
	this->posicionFinal = posicionFinal;
}

void Segmento::setPosicionInicial(Posicion* posicionInicial){
	this->posicionInicial = posicionInicial;
}

Posicion* Segmento::getPosicionFinal(){
	return this->posicionFinal;
}

Posicion* Segmento::getPosicionInicial(){
	return this->posicionInicial;
}

Segmento::~Segmento(){
	delete this->posicionFinal;
	delete this->posicionInicial;
}


