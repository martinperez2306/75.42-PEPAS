#ifndef HEADERS_MODEL_WORLD_H_
#define HEADERS_MODEL_WORLD_H_

#include <map>
#include "LineaX.h"

class World {

private:
	//Mapa <distancia (eje Y), LineaDelEjeX>
	map<int,LineaX*>* world;

public:
	World();
	void agregarLinea(int distanciaY,LineaX*);
	int obtenerElementoEnPosicion(int distanciaY, int corrimientoX);
	void agregarElementoALinea(int distanciaY,int corrimientoX, int elemento);
	~World();
};

#endif /* HEADERS_MODEL_WORLD_H_ */
