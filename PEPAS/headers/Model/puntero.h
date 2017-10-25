#ifndef PUNTERO_H_
#define PUNTERO_H_

#include "posicion.h"

class Puntero{

private:
	int angulo;
	void unificarAngulo();
	int distancia;

public:

	Puntero();

	void setDistancia(int distancia);
	int getDistancia();

	void setAngulo(int angulo);
	int getAngulo();

	void girarIzquierda();
	void girarDerecha();
	Posicion* avanzar(Posicion* posicion,int distancia);

	~Puntero();
};



#endif /* PUNTERO_H_ */
