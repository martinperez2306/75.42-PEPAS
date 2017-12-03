#include "../../headers/Model/minimapa.h"

Minimapa::Minimapa(){
	this->pista = new list<Segmento*>();
	this->objetos = new list<Objeto*>();
}

void Minimapa::agregarSegmento(Segmento* segmento){
	this->pista->push_back(segmento);
}

void Minimapa::agregarObjeto(Objeto* objeto){
	this->objetos->push_back(objeto);
}

void Minimapa::mostrarSegmentos(){
	for(list<Segmento*>::iterator it = this->pista->begin(); it != this->pista->end();++it){
		Segmento* seg = *it;
		Posicion* posicionInicial = seg->getPosicionInicial();
		Posicion* posicionFinal = seg->getPosicionFinal();
		cout<<"Posicion Incial: "<<" X "<< posicionInicial->getX()<<" Y "<<posicionInicial->getY()<<endl;
		cout<<"Posicion Final: "<<" X "<< posicionFinal->getX()<<" Y "<<posicionFinal->getY()<<endl;
	}
}

void Minimapa::mostrarObjetos(){
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

list<Segmento*>* Minimapa::getSegmentos(){
	return this->pista;
}

list<Objeto*>* Minimapa::getObjetos(){
	return this->objetos;
}

Minimapa::~Minimapa(){
	this->objetos->clear();
	this->pista->clear();
	delete this->objetos;
	delete this->pista;
}

void Minimapa::limpiarMinimapa(){
	this->pista->clear();
	this->objetos->clear();
}

