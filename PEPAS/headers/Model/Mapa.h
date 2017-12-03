#ifndef MAPA_H_
#define MAPA_H_

#include <iostream>
#include <list>
#include "Objeto.h"
#include "segmento.h"
#include <map>
#include "LineaX.h"

using namespace std;

class Mapa {

private:
	list<Objeto*>* objetos;
	list<Segmento*>* ruta;

public:
	Mapa();

	void agregarObjeto(Objeto* objeto);
	void agregarSegmento(Segmento* segmento);
	void mostrarSegmentos();
	void mostrarObjetos();
	void limpiarMapa();

	list<Segmento*>* getRuta();
	list<Objeto*>* getObjetos();

	//Eliminar las referencias a las estructuras y su contenido
	~Mapa();
};

#endif /* MAPA_H_ */
