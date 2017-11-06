#include "../../headers/com.pepas.model/Recorredor.h"

Recorredor::Recorredor() {
	this->direccionRecorrido = 0;
	this->distanciaRecorrida = 0;
	this->posicionActual = new Posicion();
	this->posicionesDeLosObjetos = new list<Posicion*>();
}

void Recorredor::setDireccionRecorrido(int direccion){
	this->direccionRecorrido = direccion;
}

void Recorredor::setDistanciaRecorrida(int distancia){
	this->distanciaRecorrida = distancia;
}

void Recorredor::setPosicionActual(Posicion* posicionActual){
	this->posicionActual = posicionActual;
}

int Recorredor::getDireccionRecorrida(){
	return this->direccionRecorrido;
}

int Recorredor::getDistanciaRecorrida(){
	return this->distanciaRecorrida;
}

Posicion* Recorredor::getPosicionActual(){
	return this->posicionActual;
}

//PARA RECORREDOR EL DELTA Y NEGATIVO REPRESENTA EL NORTE Y EL DELTA Y POSITIVO REPRESENTA EL SUR
//SDL TRABAJA CON EL EJE Y INVERTIDO A LO ORDINARIO

void Recorredor::generarDireccionRecorrido(Segmento* segmento){

	Posicion* posInicial =segmento->getPosicionInicial();
	Posicion* posFinal = segmento->getPosicionFinal();
	int x0 = posInicial->getX();
	int y0 = posInicial->getY();
	int x1 = posFinal->getX();
	int y1 = posFinal->getY();

	int anguloDireccion = 0;

	int deltaX = (x1 - x0);
	int deltaY = (y1 - y0);

	if(deltaX == 0 || deltaY == 0){
		if(deltaY == 0){
			if(deltaX > 0){
				anguloDireccion = 0;
			}
			if(deltaX < 0){
				anguloDireccion = 180;
			}
		}
		if(deltaX == 0){
			if(deltaY > 0){
				anguloDireccion = 270;
			}
			if(deltaY < 0){
				anguloDireccion = 90;
			}
		}
	}
	else{
		if(deltaX > 0 && deltaY > 0){
			anguloDireccion = 315;
		}
		if(deltaX > 0 && deltaY < 0){
			anguloDireccion = 45;
		}
		if(deltaX < 0 && deltaY > 0){
			anguloDireccion = 225;
		}
		if(deltaX < 0 && deltaY < 0){
			anguloDireccion = 135;
		}
	}

	this->direccionRecorrido = anguloDireccion;
}

bool Recorredor::equals(Posicion* posicion){
	return ((this->posicionActual->getX() == posicion->getX()) && (this->posicionActual->getY() == posicion->getY()));
}

void Recorredor::unificarAngulo(){
	if(this->direccionRecorrido < 0){
		this->direccionRecorrido += 360;
	}
	else if (this->direccionRecorrido >= 360){
		this->direccionRecorrido -= 360;
	}
}

void Recorredor::siguientePosicion(int distancia){
	switch(this->direccionRecorrido){

			case 0:
				this->posicionActual->setX(this->posicionActual->getX() + distancia);
				break;
			case 45:
				this->posicionActual->setX(this->posicionActual->getX() + distancia);
				this->posicionActual->setY(this->posicionActual->getY() - distancia);
				break;
			case 90:
				this->posicionActual->setY(this->posicionActual->getY() - distancia);
				break;
			case 135:
				this->posicionActual->setX(this->posicionActual->getX() - distancia);
				this->posicionActual->setY(this->posicionActual->getY() - distancia);
				break;
			case 180:
				this->posicionActual->setX(this->posicionActual->getX() - distancia);
				break;
			case 225:
				this->posicionActual->setX(this->posicionActual->getX() - distancia);
				this->posicionActual->setY(this->posicionActual->getY() + distancia);
				break;
			case 270:
				this->posicionActual->setY(this->posicionActual->getY() + distancia);
				break;
			case 315:
				this->posicionActual->setX(this->posicionActual->getX() + distancia);
				this->posicionActual->setY(this->posicionActual->getY() + distancia);
				break;
			}
}

void Recorredor::avanzar(){
		this->distanciaRecorrida++;
}

void Recorredor::girarDerecha(){
	this->direccionRecorrido -= 90;
	this->unificarAngulo();
}

void Recorredor::girarIzquierda(){
	this->direccionRecorrido += 90;
	this->unificarAngulo();
}

Posicion* Recorredor::generarPosicionObjeto(string ladoDelObjeto){
	Posicion* posObjeto = new Posicion();
	//Almaceno posicion actual antes de girar para mirar los objetos
	int xAux = this->posicionActual->getX();
	int yAux = this->posicionActual->getY();
	//Giramos y acomodamos segun en lado del objeto. Avanzamos a su posicion y retomamos al direccion original.
	if(ladoDelObjeto.compare("D") == 0){
		this->girarDerecha();
		this->siguientePosicion(5);
		this->girarIzquierda();
	}
	if(ladoDelObjeto.compare("I") == 0){
		this->girarIzquierda();
		this->siguientePosicion(5);
		this->girarDerecha();
	}
	//Seteamos la posicion Del objeto
	posObjeto->setX(this->posicionActual->getX());
	posObjeto->setY(this->posicionActual->getY());
	//Recuperamos la posicion actual
	this->posicionActual->setX(xAux);
	this->posicionActual->setY(yAux);
	return posObjeto;
}

void Recorredor::recorrer(Segmento* segmento,list<Objeto*>* objetos){

	this->generarDireccionRecorrido(segmento);
	this->posicionActual->setX(segmento->getPosicionInicial()->getX());
	this->posicionActual->setY(segmento->getPosicionInicial()->getY());

	while(!this->equals(segmento->getPosicionFinal())){
		for(list<Objeto*>::iterator it = objetos->begin(); it!= objetos->end(); ++it){
			Objeto* objeto = *it;
			if(this->distanciaRecorrida == objeto->getDistancia()){
				string lado = objeto->getLado();
				this->posicionesDeLosObjetos->push_back(this->generarPosicionObjeto(lado));
			}
		}
		//avanzamos a la siguiente posicion segun la direccion del recorredor y aumentamos la distancia recorrida
		this->siguientePosicion(1);
		this->avanzar();
	}
}

list<Posicion*>* Recorredor::getPosicionesDeLosObjetos(){
	return this->posicionesDeLosObjetos;
}

Recorredor::~Recorredor() {
	// TODO Auto-generated destructor stub
}

