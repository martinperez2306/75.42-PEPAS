#include "../../headers/Model/objetos.h"

Objetos::Objetos(){
	this->objetoADerecha = new Casillero();
	this->objetoAIzquierda = new Casillero();
}

void Objetos::agregarObjetoADerecha(Casillero* objeto){
	this->objetoADerecha = objeto;
}

void Objetos::agregarObjetoAIzquierda(Casillero* objeto){
	this->objetoAIzquierda= objeto;
}

Casillero* Objetos::getObjetoDerecha(){
	return this->objetoADerecha;
}

Casillero* Objetos::getObjetoIzquierda(){
	return this->objetoAIzquierda;
}

Objetos::~Objetos(){
	delete this->objetoADerecha;
	delete this->objetoAIzquierda;
}


