//
// Created by arturi on 26/11/17.
//

#include "../../headers/Model/Recorredor.h"

Recorredor::Recorredor() {
    this->direccionRecorrido = 0;
    this->distanciaRecorrida = 0;
    this->posicionActual = new Posicion();
    this->posiciones = new map<int,Posicion*>();
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

Posicion* Recorredor::generarPosicionRuta(){
    Posicion* pos = new Posicion(this->posicionActual->getX(),this->posicionActual->getY());
    return pos;
}

void Recorredor::recorrer(Segmento* segmento){
    //cout<<"entre al recorrer"<<endl;
    this->generarDireccionRecorrido(segmento);
    this->posicionActual->setX(segmento->getPosicionInicial()->getX());
    this->posicionActual->setY(segmento->getPosicionInicial()->getY());

    while(!this->equals(segmento->getPosicionFinal())){
        //agregamos la posicion al mapa de posiciones para los jugadores
        (*this->posiciones)[distanciaRecorrida] = this->generarPosicionRuta();
        //avanzamos a la siguiente posicion segun la direccion del recorredor y aumentamos la distancia recorrida
        this->siguientePosicion(1);
        this->avanzar();
    }
}

Posicion* Recorredor::getPosicionEnDistancia(int distancia){
    return this->posiciones->find(distancia)->second;
}

Recorredor::~Recorredor() {
    delete this->posicionActual;
    this->posiciones->clear();
    delete this->posiciones;
}

void Recorredor::limpiarRecorredor(){
    this->direccionRecorrido = 0;
    this->distanciaRecorrida = 0;
    this->posicionActual->setX(0);
    this->posicionActual->setY(0);
    this->posiciones->clear();
}
