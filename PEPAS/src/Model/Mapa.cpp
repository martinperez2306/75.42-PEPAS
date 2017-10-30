#include "../../headers/Model/Mapa.h"

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
		cout<<"Longitud: "<<seg->getLongitud()<<endl;
		cout<<"Curva: "<<seg->getCurva()<<endl;
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
	delete this->objetos;
	delete this->ruta;
}

