#include "/home/barbarasanchez/Desktop/75.42-PEPAS-servidor/PEPAS/headers/Model/Zoomer.h"

Zoomer::Zoomer() {
	this->tamanioZoom = 0;
	this->recta = new Recta();

}

void Zoomer::aumentar(int x, int y, int pendiente,Mapa* mapa){
	switch(pendiente){
	case 0:
		for(int i = 0 ; i<= this->tamanioZoom;i++){
			mapa->setPos(x,y+i,1);
			mapa->setPos(x,y-i,1);
		};
		break;
	case 1:
		for(int i = 0; i<= this->tamanioZoom;i++){
			mapa->setPos(x-i,y+i,1);
			mapa->setPos(x+i,y-i,1);
		}
		break;
	case -1:
		for(int i = 0; i<= this->tamanioZoom;i++){
					mapa->setPos(x+i,y+i,1);
					mapa->setPos(x-i,y-i,1);
				}
		break;
	case INFINITO:
		for(int i = 0; i<= this->tamanioZoom;i++){
					mapa->setPos(x-i,y,1);
					mapa->setPos(x+i,y,1);
				}
		break;
	}
}

void Zoomer::zoom(Mapa* mapa, Segmento* segmento, Objetos* objetos){

	Posicion* posicionInicial = segmento->getPosicionInicial();
	Posicion* posicionFinal = segmento->getPosicionFinal();

	this->recta->calcularEcuacionDeLaRecta(posicionInicial->getX(),posicionInicial->getY(),posicionFinal->getX(),posicionFinal->getY());

	int deltaX = (posicionFinal->getX() - posicionInicial->getX());
	int deltaY = (posicionFinal->getY() - posicionInicial->getY());

	if(deltaX != 0){
		if(deltaX > 0){
		for(int x = posicionInicial->getX(); x < posicionFinal->getX();x++){
			int y = this->recta->calcularY(x);
			this->aumentar(x,y,this->recta->getA(),mapa);
		}
		}else{
		for(int x = posicionFinal->getX();x < posicionInicial->getX();x++){
			int y = this->recta->calcularY(x);
			this->aumentar(x,y,this->recta->getA(),mapa);
		}
		}
	}else{
		if(deltaY > 0){
			for(int y = posicionInicial->getY(); y < posicionFinal->getY();y++){
				this->aumentar(posicionInicial->getX(),y,INFINITO,mapa);
			}
		}else{
			for(int y = posicionFinal->getY();y < posicionInicial->getY();y++){
				this->aumentar(posicionInicial->getX(),y,INFINITO,mapa);
			}
		}
	}

}

void Zoomer::zoomMinimapToMap(Minimapa* minimapa,Mapa* mapa){
	for (map<Segmento*,Objetos*>::iterator it=minimapa->getMinimapa()->begin(); it!=minimapa->getMinimapa()->end(); ++it){
		    Segmento* segmento = it->first;
		    Objetos* objetos = it->second;
		    this->zoom(mapa,segmento,objetos);
		}
}

void Zoomer::setTamanioZoom(int tamanioZoom){
	this->tamanioZoom = tamanioZoom;
}

Zoomer::~Zoomer() {
	// TODO Auto-generated destructor stub
}

