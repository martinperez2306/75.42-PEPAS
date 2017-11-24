#ifndef OBJETOS_H_
#define OBJETOS_H_

#include <iostream>


using namespace std;

class Objetos{

	//LOS OBJETOS SON AQUELLOS ITEMS QUE ESTAN A LA IZQUIERDA Y/O DERECHA DEL SEGMENTO (CONJUNTO DE RECTAS).
private:
	int objetoADerecha;
	int objetoAIzquierda;

public:
	Objetos();

	void agregarObjetoADerecha(int objeto);
	void agregarObjetoAIzquierda(int objeto);

	int getObjetoDerecha();
	int getObjetoIzquierda();

	void mostrarObjetos();
	~Objetos();
};



#endif /* OBJETOS_H_ */
