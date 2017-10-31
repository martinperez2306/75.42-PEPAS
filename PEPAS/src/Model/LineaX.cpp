#include "../../headers/Model/LineaX.h"

LineaX::LineaX() {
	this->lineaX = new map<int,int>();
	this->curva = 0;
}

void LineaX::inicializarLinea(){
	for(int i = 0; i < 7; i++){
		(*this->lineaX)[i] = 0;
	}
}

void LineaX::agregarElemento(int posicionX,int elemento){
	(*this->lineaX)[posicionX] = elemento;
}

void LineaX::setCurva(int curva){
	this->curva = curva;
}

int LineaX::getCurva(){
	return this->curva;
}

int LineaX::obtenerElemento(int posicionX){
	return this->lineaX->find(posicionX)->second;
}

LineaX::~LineaX() {
	delete this->lineaX;
}

