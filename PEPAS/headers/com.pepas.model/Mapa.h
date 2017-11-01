#ifndef COM_PEPAS_MODEL_MAPA_H_
#define COM_PEPAS_MODEL_MAPA_H_

#include <list>
#include "Objeto.h"
#include "segmento.h"

using namespace std;
class Mapa {

private:

	list<Segmento*>* ruta;
	list<Objeto*>* objetos;
public:
	Mapa();

	void agregarSegmento(Segmento* segmento);
	void agregarObjeto(Objeto* objeto);

	list<Segmento*>* obtenerRuta();
	list<Objeto*>* obtenerObjetos();
	void mostrarObjetos();
	void mostrarSegmentos();
	~Mapa();
};

#endif /* COM_PEPAS_MODEL_MAPA_H_ */
