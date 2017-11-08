#include "../../headers/Model/LineaX.h"

LineaX::LineaX() {
	this->curva = 0;
}


void LineaX::setCurva(int curva){
	this->curva = curva;
}

int LineaX::getCurva(){
	return this->curva;
}

LineaX::~LineaX() {
}

