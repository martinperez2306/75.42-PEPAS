#ifndef SEGMENTO_H_
#define SEGMENTO_H_

#include "posicion.h"
#include <iostream>

class Segmento{


//EL SEGMENTO ACA SE INTERPRETA UNICAMENTE COMO UNA RECTA
private:
	Posicion* posicionInicial;
	Posicion* posicionFinal;


public:


	Segmento();

	Segmento(Posicion* posInicial,Posicion* posFinal);

	Posicion* getPosicionInicial();
	Posicion* getPosicionFinal();

	~Segmento();
};



#endif /* SEGMENTO_H_ */
