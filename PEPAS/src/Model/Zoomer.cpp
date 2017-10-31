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

void Zoomer::zoomMapToWorld(Mapa* mapa, World* world){

	int metros = 0;
	int distanciaRecorrida;
	//Para todos los segmentos, agregar el kilometraje y su linea X correspondiente
	for(list<Segmento*>::iterator it = mapa->getRuta()->begin(); it!= mapa->getRuta()->end(); ++it){
		Segmento* segmento = *it;
		int distancia = segmento->getLongitud();
		for(distanciaRecorrida = 0; distanciaRecorrida < distancia ; distanciaRecorrida++){
			LineaX* lineaX = new LineaX();
			lineaX->inicializarLinea();
			lineaX->setCurva(segmento->getCurva());
			world->agregarLinea(distanciaRecorrida,lineaX);
		}

	}
	//Agregar todos los objetos al world, en su correspondiente kilometraje y posicionamiento de x
	//Por ahora tomemos como que si el valor del elemento es 0 no hay nada y si el valor es 1 hay algo Luego vemos como hacemos
	//con los autos y los objetos (arbol y cartel)
	distanciaRecorrida = 0;
	for(list<Objeto*>::iterator it = mapa->getObjetos()->begin(); it!=mapa->getObjetos()->end();++it){
		Objeto* objeto = *it;
		int distanciaObjeto = objeto->getDistancia();
		//El 100000 es un duro harcodeo pero esta por las dudas por si algo se hace poronga y se queda ahi en el loop
		while(distanciaRecorrida != distanciaObjeto && distanciaRecorrida < 100000){
			distanciaRecorrida++;
		}
		if(distanciaRecorrida == distanciaObjeto){
			if(objeto->getLado().compare("D")){
				//en 6 esta ya el fuera de pista derecha (tambien esta el 5)
				//el 1 es para un objeto cualquiera
				world->agregarElementoALinea(distanciaRecorrida,6,1);
			}
			if(objeto->getLado().compare("I")){
				//en 0 esta ya el fuera de pusta izquierda (tambien el 1)
				//el 1 es igual que antes..
				world->agregarElementoALinea(distanciaRecorrida,0,1);
			}
		}
	}

}

Zoomer::~Zoomer() {
}

