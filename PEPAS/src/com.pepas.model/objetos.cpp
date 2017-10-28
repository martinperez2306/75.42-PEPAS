#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/objetos.h"

Objetos::Objetos(){
	this->objetoADerecha = 0;
	this->objetoAIzquierda = 0;
}

void Objetos::agregarObjetoADerecha(int objeto){
	this->objetoADerecha = objeto;
}

void Objetos::agregarObjetoAIzquierda(int objeto){
	this->objetoAIzquierda= objeto;
}

int Objetos::getObjetoDerecha(){
	return this->objetoADerecha;
}

int Objetos::getObjetoIzquierda(){
	return this->objetoAIzquierda;
}

Objetos::~Objetos(){
}


