#include "../../headers/com.pepas.model/Objeto.h"



Objeto::Objeto() {
	this->arbol = 0;
	this->cartel = 0;
	this->distancia = 0;
	this->lado = "";
}

void Objeto::setArbol(int arbol){
	this->arbol = arbol;
}

void Objeto::setCartel(int velocidadMaxima){
	this->cartel = velocidadMaxima;
}

int Objeto::getArbol(){
	return this->arbol;
}

int Objeto::getCartel(){
	return this->cartel;
}

void Objeto::setDistancia(int distancia){
	this->distancia = distancia;
}

void Objeto::setLado(string lado){
	this->lado = lado;
}

int Objeto::getDistancia(){
	return this->distancia;
}

string Objeto::getLado(){
	return this->lado;
}

Objeto::~Objeto() {
	// TODO Auto-generated destructor stub
}


