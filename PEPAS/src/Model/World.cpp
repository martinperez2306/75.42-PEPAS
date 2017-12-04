#include "../../headers/Model/World.h"

World::World() {
	this->world = new map<int,LineaX*>();
	this->finDePista = 0;
}

void World::agregarLinea(int distanciaY, LineaX* lineaX){
	(*this->world)[distanciaY] = lineaX;
}

int World::obtenerCurvaEnKilometraje(int distanciaY){
	return this->world->find(distanciaY)->second->getCurva();
}

World::~World() {
	this->world->clear();
	delete this->world;
}

void World::setFinDePista(int finDePista){
	this->finDePista = finDePista;
}

int World::getFinDePista(){
	return this->finDePista;
}

bool World::carreraHaTerminado(int posicionDeAuto){
	return (posicionDeAuto >= this->finDePista);
}

void World::limpiarWolrd(){
	this->finDePista = 0;
	this->world->clear();
}

map<int,LineaX*>* World::getWorld(){
	return this->world;
}
