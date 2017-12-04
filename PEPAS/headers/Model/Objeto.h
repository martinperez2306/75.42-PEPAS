#ifndef OBJETO_H_
#define OBJETO_H_

#include "posicion.h"
#include <iostream>

#define ARBOL 1

using namespace std;

class Objeto {

private:
	int arbol;
	int cartel;
	int distancia;
	string lado;

public:
	Objeto();

	void setArbol(int arbol);
	void setCartel(int velocidadMaxima);
	void setDistancia(int distancia);
	void setLado(string lado);

	int getArbol();
	int getCartel();
	int getDistancia();
	string getLado();

	~Objeto();
};


#endif /* OBJETO_H_ */
