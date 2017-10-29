#include "../../headers/Model/Mapa.h"

Mapa::Mapa(int lengthX, int lengthY) {
	this->mapa = NULL;
	this->lengthX = lengthX;
	this->lengthY = lengthY;
	this->inicializarMapa();
}

Mapa::Mapa(){
	this->ruta = new list<Segmento*>();
	this->objetos = new list<Objeto*>();
}

void Mapa::agregarObjeto(Objeto* objeto){
	this->objetos->push_back(objeto);
}

void Mapa::agregarSegmento(Segmento* segmento){
	this->ruta->push_back(segmento);
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

list<Segmento*>* Mapa::getRuta(){
	return this->ruta;
}

list<Objeto*>* Mapa::getObjetos(){
	return this->objetos;
}

void Mapa::mostrarSegmentos(){
	for(list<Segmento*>::iterator it = this->ruta->begin(); it != this->ruta->end();++it){
		Segmento* seg = *it;
		Posicion* posicionInicial = seg->getPosicionInicial();
		Posicion* posicionFinal = seg->getPosicionFinal();
		cout<<"Posicion Incial: "<<" X "<< posicionInicial->getX()<<" Y "<<posicionInicial->getY()<<endl;
		cout<<"Posicion Final: "<<" X "<< posicionFinal->getX()<<" Y "<<posicionFinal->getY()<<endl;
	}
}

void Mapa::mostrarObjetos(){
	for(list<Objeto*>::iterator it = this->objetos->begin(); it != this->objetos->end();++it){
		Objeto* obj = *it;
		int distancia = obj->getDistancia();
		int arbol = obj->getArbol();
		int cartel = obj->getCartel();
		cout<<"Objeto"<<endl;
		cout<<"Arbol: "<<arbol<<" Cartel: "<<cartel<<endl;
		cout<<"Distancia: "<<distancia<<endl;
		cout<<"Lado: "<<obj->getLado()<<endl;
	}
}

Mapa::~Mapa() {
	delete this->mapa;
}

