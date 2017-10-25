#include "/home/barbarasanchez/Desktop/75.42-PEPAS-servidor/PEPAS/headers/Model/segmento.h"

Segmento::Segmento(){
	this->posicionFinal= NULL;
	this->posicionInicial= NULL;
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


