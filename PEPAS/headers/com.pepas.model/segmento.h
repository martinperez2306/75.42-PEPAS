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

	//Eliminar memoria pedida para la posicion Inicia y pos final (el delete verifica si alguna de las dos ya fue
	//eliminada por otro segmento, ya que segmentos pueden compartir una misma pos)
	~Segmento();
};



#endif /* SEGMENTO_H_ */
