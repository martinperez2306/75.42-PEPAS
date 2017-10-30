#include "../../headers/Model/Zoomer.h"

Zoomer::Zoomer() {
	this->tamanioZoom = 0;
	this->recta = new Recta();

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

void Zoomer::zoomMapToMinimap(Mapa* mapa, Minimapa* minimapa){
	for(list<Segmento*>::iterator it = mapa->getRuta()->begin(); it!= mapa->getRuta()->end(); ++it){
		Segmento* segmento = *it;
		Segmento* segmentoMinimapa = this->zoomRuta(segmento);
		minimapa->agregarSegmento(segmentoMinimapa);
	}
	for(list<Objeto*>::iterator it = mapa->getObjetos()->begin(); it!=mapa->getObjetos()->end();++it){
		Objeto* objeto = *it;
		minimapa->agregarObjeto(this->zoomObjeto(objeto));
	}
}

void Zoomer::setTamanioZoom(int tamanioZoom){
	this->tamanioZoom = tamanioZoom;
}

Zoomer::~Zoomer() {
	delete this->recta;
}

