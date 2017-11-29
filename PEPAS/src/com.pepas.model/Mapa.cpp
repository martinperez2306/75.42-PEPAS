#include "../../headers/com.pepas.model/Mapa.h"

Mapa::Mapa() {
	this->ruta = new list<Segmento*>();
	this->objetos = new list<Objeto*>();
}

void Mapa::agregarObjeto(Objeto* objeto){
	this->objetos->push_back(objeto);
}

void Mapa::agregarSegmento(Segmento* segmento){
	this->ruta->push_back(segmento);
}

list<Segmento*>* Mapa::obtenerRuta(){
	return this->ruta;
}

list<Objeto*>* Mapa::obtenerObjetos(){
	return this->objetos;
}

//COPIE PASTEE LO DE SERVIDOR PARA QUE TE IMPRIMA LOS OBJETOS
void Mapa::mostrarSegmentos(){
	for(list<Segmento*>::iterator it = this->ruta->begin(); it != this->ruta->end();++it){
		Segmento* seg = *it;
		int longitud = seg->getLongitud();
		int curva = seg->getCurva();
		cout<<"Longitud: "<<longitud<<endl;
		cout<<"Curva: "<<curva<<endl;
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

//ACA MANEJATE VO TURI COMO DESEAS ADMINISTRAR LA MEMORIA
Mapa::~Mapa() {
	// TODO Auto-generated destructor stub
}

void Mapa::limpiarMapa(){
	this->objetos->clear();
	this->ruta->clear();
}

