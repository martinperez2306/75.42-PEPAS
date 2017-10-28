#ifndef PUNTERO_H_
#define PUNTERO_H_

#include "posicion.h"
#include <string>
using namespace std;

class Puntero{

private:
	int angulo;
	void unificarAngulo();
	int distanciaRecorrida;

public:

	Puntero();

	void setDistancia(int distancia);
	int getDistancia();

	void setAngulo(int angulo);
	int getAngulo();

	void girarIzquierda();
	void girarDerecha();
	Posicion* avanzar(Posicion* posicion,int distancia);
	Posicion* calcularPosicionObjeto(string posicion);

	~Puntero();
};



#endif /* PUNTERO_H_ */
