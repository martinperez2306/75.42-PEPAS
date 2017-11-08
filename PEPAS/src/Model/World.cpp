#include "../../headers/Model/World.h"

World::World() {
	this->world = new map<int,LineaX*>();
}

void World::agregarLinea(int distanciaY, LineaX* lineaX){
	(*this->world)[distanciaY] = lineaX;
}

int World::obtenerCurvaEnKilometraje(int distanciaY){
	return this->world->find(distanciaY)->second->getCurva();
}

World::~World() {
	delete this->world;
}

