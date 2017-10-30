#ifndef SEGMENTO_H_
#define SEGMENTO_H_

#include "posicion.h"
#include <iostream>

class Segmento{


//EL SEGMENTO ACA SE INTERPRETA UNICAMENTE COMO UNA RECTA
private:
	Posicion* posicionInicial;
	Posicion* posicionFinal;
	int longitud;
	//Recta = 0 Curva I = 1 Curva D = -1
	int curva;

public:


	Segmento();

	Segmento(Posicion* posInicial,Posicion* posFinal);

	void setCurva(int curva);
	void setLongitud(int longitud);
	void setPosicionInicial(Posicion* posicionInicial);
	void setPosicionFinal(Posicion* posicionFinal);

	Posicion* getPosicionInicial();
	Posicion* getPosicionFinal();
	int getLongitud();
	int getCurva();

	//Eliminar memoria pedida para la posicion Inicia y pos final (el delete verifica si alguna de las dos ya fue
	//eliminada por otro segmento, ya que segmentos pueden compartir una misma pos)
	~Segmento();
};



#endif /* SEGMENTO_H_ */
