#ifndef OBJETOS_H_
#define OBJETOS_H_

#include "casillero.h"
#include <iostream>

using namespace std;

class Objetos{

	//LOS OBJETOS SON AQUELLOS ITEMS QUE ESTAN A LA IZQUIERDA Y/O DERECHA DEL SEGMENTO (CONJUNTO DE RECTAS).
private:
	Casillero* objetoADerecha;
	Casillero* objetoAIzquierda;

public:
	Objetos();

	void agregarObjetoADerecha(Casillero* objeto);
	void agregarObjetoAIzquierda(Casillero* objeto);

	Casillero* getObjetoDerecha();
	Casillero* getObjetoIzquierda();

	void mostrarObjetos();

	~Objetos();
};



#endif /* OBJETOS_H_ */
