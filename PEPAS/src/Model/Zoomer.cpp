#include "../../headers/Model/Zoomer.h"

Zoomer::Zoomer() {
	this->tamanioZoom = 0;

}

Segmento* Zoomer::zoomRuta(Segmento* segmento){
	Segmento* segmentoZoom = new Segmento();
	Posicion* posicionInicialZoom = new Posicion();
	Posicion* posicionFinalZoom = new Posicion();
	posicionInicialZoom->setX(segmento->getPosicionInicial()->getX() / this->tamanioZoom);
	posicionInicialZoom->setY(segmento->getPosicionInicial()->getY() / this->tamanioZoom);
	posicionFinalZoom->setX(segmento->getPosicionFinal()->getX() / this->tamanioZoom);
	posicionFinalZoom->setY(segmento->getPosicionFinal()->getY() / this->tamanioZoom);
	segmentoZoom->setPosicionInicial(posicionInicialZoom);
	segmentoZoom->setPosicionFinal(posicionFinalZoom);
	segmentoZoom->setCurva(segmento->getCurva());
	segmentoZoom->setLongitud(segmento->getLongitud() / this->tamanioZoom);
	return segmentoZoom;
}

Objeto* Zoomer::zoomObjeto(Objeto* objeto){
	Objeto* objetoMinimapa = new Objeto();
	objetoMinimapa->setArbol(objeto->getArbol());
	objetoMinimapa->setCartel(objeto->getCartel());
	objetoMinimapa->setLado(objeto->getLado());
	objetoMinimapa->setDistancia(objeto->getDistancia() / this->tamanioZoom);
	return objetoMinimapa;
}

void Zoomer::setTamanioZoom(int tamanioZoom){
	this->tamanioZoom = tamanioZoom;
}

void Zoomer::zoomMapToWorld(Mapa* mapa, World* world){

	int metros = 0;
	int distanciaRecorrida;
	//Para todos los segmentos, agregar el kilometraje y su linea X correspondiente
	for(list<Segmento*>::iterator it = mapa->getRuta()->begin(); it!= mapa->getRuta()->end(); ++it){
		Segmento* segmento = *it;
		int distancia = segmento->getLongitud();
		for(distanciaRecorrida = 0; distanciaRecorrida < distancia ; distanciaRecorrida++){
			LineaX* lineaX = new LineaX();
			lineaX->setCurva(segmento->getCurva());
			world->agregarLinea(metros,lineaX);
			metros++;
		}
	}
	//seteamos el final de pista
	world->setFinDePista(4900);
	//agregamos padding al final
	this->agregarPaddingToWorld(world,metros);
}

//Modifica el metodo zoomPamToMinimap del zoomer.h y el codigo del .cpp reemplazalo por esto (el cout fue de debug)
void Zoomer::zoomMapToMinimap(Mapa* mapa, Minimapa* minimapa,Recorredor* recorredor){
	cout<<"entre al zoomer"<<endl;
	for(list<Segmento*>::iterator it = mapa->getRuta()->begin(); it!= mapa->getRuta()->end(); ++it){
		Segmento* segmento = *it;
		Segmento* segmentoMinimapa = this->zoomRuta(segmento);
		minimapa->agregarSegmento(segmentoMinimapa);
		recorredor->recorrer(segmentoMinimapa);
	}
	for(list<Objeto*>::iterator it = mapa->getObjetos()->begin(); it!=mapa->getObjetos()->end();++it){
		Objeto* objeto = *it;
		minimapa->agregarObjeto(this->zoomObjeto(objeto));
	}
}

void Zoomer::agregarPaddingToWorld(World* world, int metrosFinales){

	for(int i = 1; i <= PADDING ; i++){
		metrosFinales++;
		LineaX* lineaX = new LineaX();
		//RECTA
		lineaX->setCurva(0);
		world->agregarLinea(metrosFinales,lineaX);
	}
}


Zoomer::~Zoomer() {
}

