#include "/home/barbarasanchez/Desktop/75.42-PEPAS-servidor/PEPAS/headers/Model/casillero.h"


Casillero::Casillero(){
	this->pista = VACIO;
	this->arbol = VACIO;
	this->cartel = VACIO;
}

void Casillero::setPista(int pista){
	this->pista = pista;
}

void Casillero::setArbol(int arbol){
	this->arbol = arbol;
}

void Casillero::setPista(){
	this->pista = PISTA;
}

void Casillero::setArbol(){
	this->arbol = ARBOL;
}

void Casillero::setCartel(int velocidadMaxima){
	this->cartel = velocidadMaxima;
}

int Casillero::getArbol(){
	return this->arbol;
}

int Casillero::getPista(){
	return this->pista;
}

int Casillero::getCartel(){
	return this->cartel;
}

Casillero::~Casillero(){

}

