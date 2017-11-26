#include "../../headers/com.pepas.model/minimapa.h"

typedef pair<Segmento*,Objetos*> segObj;

Minimapa::Minimapa(){
	this->minimapa = new map<Segmento*,Objetos*>();
	this->ruta = new list<Segmento*>();
	this->objetos = new list<Objeto*>();
	this->radar = new map<int,Posicion*>();
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

void Minimapa::mostrarSegmentos(){
	for(list<Segmento*>::iterator it = this->ruta->begin(); it != this->ruta->end();++it){
		Segmento* seg = *it;
		Posicion* posicionInicial = seg->getPosicionInicial();
		Posicion* posicionFinal = seg->getPosicionFinal();
		/*cout<<"Posicion Incial: "<<" X "<< posicionInicial->getX()<<" Y "<<posicionInicial->getY()<<endl;
		cout<<"Posicion Final: "<<" X "<< posicionFinal->getX()<<" Y "<<posicionFinal->getY()<<endl;*/
	}
}

void Minimapa::mostrarObjetos(){
	for(list<Objeto*>::iterator it = this->objetos->begin(); it != this->objetos->end();++it){
		Objeto* obj = *it;
		int distancia = obj->getDistancia();
		int arbol = obj->getArbol();
		int cartel = obj->getCartel();
		/*cout<<"Objeto"<<endl;
		cout<<"Arbol: "<<arbol<<" Cartel: "<<cartel<<endl;
		cout<<"Distancia: "<<distancia<<endl;
		cout<<"Lado: "<<obj->getLado()<<endl;*/
	}
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

void Minimapa::setAutoEnRadar(int player,Posicion* posicion){
	(*this->radar)[player] = posicion;
}

/*Posicion* Minimapa::getPosicionDelAutoEnRadar(int player){
	return this->radar->find(player)->second;
}*/

map<int,Posicion*>* Minimapa::getRadar(){
	return this->radar;
}
