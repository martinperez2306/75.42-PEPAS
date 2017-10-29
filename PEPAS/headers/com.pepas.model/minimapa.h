#ifndef MINIMAPA_H_
#define MINIMAPA_H_

#include <map>
#include <iomanip>
#include <string>
#include <utility>
#include <iostream>
#include <list>

#include "segmento.h"
#include "objetos.h"
#include "Objeto.h"

using namespace std;

class Minimapa{

private:
	map<Segmento*,Objetos*>* minimapa;
	list<Segmento*>* ruta;
	list<Objeto*>* objetos;

public:

	//EL MINIMAPA ESTA COMPUESTO POR SEGMENTOS QUE SON INTERPERTADOS POR UNA O MAS RECTAS (PUEDEN DEFINIR CURVAS)
	//ES UN CONJUNTO DE SUBSEGMENTOS (LA CLASE SEGMENTOS REPRESENTA ESTOS SUBSEGMENTOS)
	Minimapa();

	void setObjetos(Segmento* seg,Objetos* objetos);
	void setLengthX(int x);
	void setLengthY(int y);

	void agregarSegmento(Segmento* segmento);
	void agregarObjetos(Objeto* objeto);

	int getLengthX();
	int getLengthY();

	map<Segmento*,Objetos*>* getMinimapa();
	list<Segmento*>* getRuta();
	list<Objeto*>* getObjetos();

	void mostrarSegmentos();
	void mostrarObjetos();
	void getAllPosiciones();

	//Eliminar la memoria pedida por el minimapa
	//Eliminar toda la memoria pedida para los segmentos y los objetos
	~Minimapa();
};




#endif /* MINIMAPA_H_ */
