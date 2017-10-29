#include "../../headers/Model/minimapa.h"

typedef pair<Segmento*,Objetos*> segObj;

Minimapa::Minimapa(){
	this->minimapa = new map<Segmento*,Objetos*>();
	this->pista = new list<Segmento*>();
	this->objetos = new list<Objeto*>();
}

void Minimapa::setObjetos(Segmento* seg,Objetos* objetos){
	this->minimapa->insert(segObj(seg,objetos));
}

void Minimapa::agregarSegmento(Segmento* segmento){
	this->pista->push_back(segmento);
}

void Minimapa::agregarObjeto(Objeto* objeto){
	this->objetos->push_back(objeto);
}

void Minimapa::getAllPosiciones(){
	for (map<Segmento*,Objetos*>::iterator it=this->minimapa->begin(); it!=this->minimapa->end(); ++it){
	    cout<<"Posicion Incial: "<<" X "<< it->first->getPosicionInicial()->getX()<<" Y "<<it->first->getPosicionInicial()->getY()<<endl;
	    cout<<"Posicion Final: "<<" X "<< it->first->getPosicionFinal()->getX()<<" Y "<<it->first->getPosicionFinal()->getY()<<endl;
	    cout<<"Objetos Derecha:  "<<"arbol:"<<it->second->getObjetoDerecha()->getArbol()<<" cartel:"<<it->second->getObjetoDerecha()->getCartel()<<endl;
	    cout<<"Objetos Izquierda: "<<"arbol:"<<it->second->getObjetoIzquierda()->getArbol()<<" cartel:"<<it->second->getObjetoIzquierda()->getCartel()<<endl;
	}

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

map<Segmento*,Objetos*>* Minimapa::getMinimapa(){
	return this->minimapa;
}

list<Segmento*>* Minimapa::getSegmentos(){
	return this->pista;
}

list<Objeto*>* Minimapa::getObjetos(){
	return this->objetos;
}

Minimapa::~Minimapa(){

}

