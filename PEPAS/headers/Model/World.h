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
	void agregarLinea(int distanciaY,LineaX* lineaX);
	int obtenerCurvaEnKilometraje(int distanciaY);
	~World();
};

#endif /* HEADERS_MODEL_WORLD_H_ */
