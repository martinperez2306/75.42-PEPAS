#ifndef RECORREDOR_H_
#define RECORREDOR_H_

#include <list>

#include "posicion.h"
#include "segmento.h"
#include "Objeto.h"

using namespace std;
class Recorredor {

private:
	int distanciaRecorrida;
	int direccionRecorrido;
	Posicion* posicionActual;
	list<Posicion*>* posicionesDeLosObjetos;
	void generarDireccionRecorrido(Segmento* segmento);
	bool equals(Posicion* posicion);
	void avanzar();
	void girarDerecha();
	void girarIzquierda();
	Posicion* generarPosicionObjeto(string ladoDelObjeto);
	void siguientePosicion(int distancia);

public:
	Recorredor();

	void setDistanciaRecorrida(int distancia);
	void setDireccionRecorrido(int direccion);
	void setPosicionActual(Posicion* posicionActual);

	int getDistanciaRecorrida();
	int getDireccionRecorrida();
	Posicion* getPosicionActual();

	list<Posicion*>* getPosicionesDeLosObjetos();

	void recorrer(Segmento* segmento,list<Objeto*>* objetos);
	~Recorredor();
};

#endif /* RECORREDOR_H_ */
