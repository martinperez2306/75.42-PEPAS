#include "../../headers/com.pepas.model/minimapa.h"

typedef pair<Segmento*,Objetos*> segObj;

Minimapa::Minimapa(){
	this->minimapa = new map<Segmento*,Objetos*>();
	this->ruta = new list<Segmento*>();
	this->objetos = new list<Objeto*>();
}

void Minimapa::setObjetos(Segmento* seg,Objetos* objetos){
	this->minimapa->insert(segObj(seg,objetos));
}

void Minimapa::agregarSegmento(Segmento* segmento){
	this->ruta->push_back(segmento);
}

void Minimapa::agregarObjetos(Objeto* objeto){
	this->objetos->push_back(objeto);
}


void Minimapa::getAllPosiciones(){
	for (map<Segmento*,Objetos*>::iterator it=this->minimapa->begin(); it!=this->minimapa->end(); ++it){
	    cout<<"Posicion Incial: "<<" X "<< it->first->getPosicionInicial()->getX()<<" Y "<<it->first->getPosicionInicial()->getY()<<endl;
	    cout<<"Posicion Final: "<<" X "<< it->first->getPosicionFinal()->getX()<<" Y "<<it->first->getPosicionFinal()->getY()<<endl;
	    cout<<"Objetos Derecha:  "<<"arbol:"<<it->second->getObjetoDerecha()<<" cartel:"<<it->second->getObjetoDerecha()<<endl;
	    cout<<"Objetos Izquierda: "<<"arbol:"<<it->second->getObjetoIzquierda()<<" cartel:"<<it->second->getObjetoIzquierda()<<endl;
	}

}

map<Segmento*,Objetos*>* Minimapa::getMinimapa(){
	return this->minimapa;
}

list<Segmento*>* Minimapa::getRuta(){
	return this->ruta;
}

list<Objeto*>* Minimapa::getObjetos(){
	return this->objetos;
}

Minimapa::~Minimapa(){
	for (map<Segmento*,Objetos*>::iterator it=this->minimapa->begin(); it!=this->minimapa->end(); ++it){
		Segmento* seg = it->first;
		Objetos* objs = it->second;

		this->minimapa->erase(it);

		delete seg;
		delete objs;
	}
	delete this->minimapa;
}

