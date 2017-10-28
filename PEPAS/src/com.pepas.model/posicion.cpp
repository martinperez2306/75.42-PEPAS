#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/posicion.h"

Posicion::Posicion(){

	this->x = 0;
	this->y = 0;
}

Posicion::Posicion(int x,int y){
	this->x = x;
	this->y = y;
}

void Posicion::setX(int x){
	this->x = x;
}

void Posicion::setY(int y){
	this->y = y;
}

int Posicion::getX(){
	return this->x;
}

int Posicion::getY(){
	return this->y;
}

Posicion::~Posicion(){

}
