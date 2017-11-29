//
// Created by arturi on 26/11/17.
//



#ifndef RECORREDOR_H_
#define RECORREDOR_H_

#include <list>

#include "posicion.h"
#include "segmento.h"
#include <map>

using namespace std;
class Recorredor {

private:
    int distanciaRecorrida;
    int direccionRecorrido;
    Posicion* posicionActual;
    void generarDireccionRecorrido(Segmento* segmento);
    bool equals(Posicion* posicion);
    void avanzar();
    void siguientePosicion(int distancia);
    void unificarAngulo();
    map<int,Posicion*>* posiciones;
    Posicion* generarPosicionRuta();

public:
    Recorredor();

    void setDistanciaRecorrida(int distancia);
    void setDireccionRecorrido(int direccion);
    void setPosicionActual(Posicion* posicionActual);

    int getDistanciaRecorrida();
    int getDireccionRecorrida();
    Posicion* getPosicionActual();
    Posicion* getPosicionEnDistancia(int distancia);
    void recorrer(Segmento* segmento);
    void limpiarRecorredor();
    ~Recorredor();
};

#endif /* RECORREDOR_H_ */
