#ifndef MAPA_H_
#define MAPA_H_

#include <iostream>
#include <list>
#include "Objeto.h"
#include "segmento.h"

using namespace std;

class Mapa {

private:
	int** mapa;
	int lengthX;
	int lengthY;
	void inicializarMapa();

	list<Objeto*>* objetos;
	list<Segmento*>* ruta;
public:
	Mapa(int lengthX,int lengthY);
	Mapa();

	void agregarObjeto(Objeto* objeto);
	void agregarSegmento(Segmento* segmento);
	void mostrarMapa();
	void setPos(int x, int y,int value);
	void mostrarSegmentos();
	void mostrarObjetos();

	int getPos(int x,int y);
	list<Segmento*>* getRuta();
	list<Objeto*>* getObjetos();

	~Mapa();
};

#endif /* MAPA_H_ */
