#include "/home/barbarasanchez/Desktop/75.42-PEPAS-servidor/PEPAS/headers/Model/minimapa.h"

typedef pair<Segmento*,Objetos*> segObj;

Minimapa::Minimapa(){
	this->minimapa = new map<Segmento*,Objetos*>();
}

void Minimapa::setObjetos(Segmento* seg,Objetos* objetos){
	this->minimapa->insert(segObj(seg,objetos));
}


void Minimapa::getAllPosiciones(){
	for (map<Segmento*,Objetos*>::iterator it=this->minimapa->begin(); it!=this->minimapa->end(); ++it){
	    cout<<"Posicion Incial: "<<" X "<< it->first->getPosicionInicial()->getX()<<" Y "<<it->first->getPosicionInicial()->getY()<<endl;
	    cout<<"Posicion Final: "<<" X "<< it->first->getPosicionFinal()->getX()<<" Y "<<it->first->getPosicionFinal()->getY()<<endl;
	    cout<<"Objetos Derecha:  "<<"arbol:"<<it->second->getObjetoDerecha()->getArbol()<<" cartel:"<<it->second->getObjetoDerecha()->getCartel()<<endl;
	    cout<<"Objetos Izquierda: "<<"arbol:"<<it->second->getObjetoIzquierda()->getArbol()<<" cartel:"<<it->second->getObjetoIzquierda()->getCartel()<<endl;
	}

}

map<Segmento*,Objetos*>* Minimapa::getMinimapa(){
	return this->minimapa;
}

Minimapa::~Minimapa(){
	delete this->minimapa;
}

