#include "World.h"

World::World() {
	this->world = new map<int,LineaX*>();
}

void World::agregarLinea(int distanciaY, LineaX* lineaX){
	this->world[distanciaY] = lineaX;
}

int World::obtenerElementoEnPosicion(int distanciaY,int corrimientoX){
	return this->world->find(distanciaY)->second->obtenerElemento(corrimientoX);
}

void World::agregarElementoALinea(int distanciaY,int corrimientoX, int elemento){
	this->world->find(distanciaY)->second->agregarElemento(corrimientoX,elemento);
}

World::~World() {
	delete this->world;
}

