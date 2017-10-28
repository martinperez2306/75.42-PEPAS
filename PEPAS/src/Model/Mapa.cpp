#include "../../headers/Model/Mapa.h"

Mapa::Mapa(int lengthX, int lengthY) {
	this->mapa = NULL;
	this->lengthX = lengthX;
	this->lengthY = lengthY;
	this->inicializarMapa();
}

void Mapa::inicializarMapa(){

	this->mapa = new int*[this->lengthX];
	for (int i = 0; i<this->lengthX; i++){
		this->mapa[i] = new int[lengthY];
	}
	for(int i = 0; i<this->lengthX;i++){
		for(int j=0;j<this->lengthY;j++){
			this->mapa[i][j] = 0;
		}
	}
}

void Mapa::mostrarMapa(){
	for (int i = 0; i<this->lengthX; i++){
			for (int j = 0; j<this->lengthY;j++){
				cout<<this->mapa[i][j]<<" ";
			}
			cout<<""<<endl;
		}
}

void Mapa::setPos(int x,int y, int value){
	this->mapa[y][x] = value;
}

int Mapa::getPos(int x, int y){
	return this->mapa[y][x];
}

Mapa::~Mapa() {
	delete this->mapa;
}

