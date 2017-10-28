#ifndef MINIMAPA_H_
#define MINIMAPA_H_

#include <map>
#include <iomanip>
#include <string>
#include <utility>
#include <iostream>

#include "segmento.h"
#include "objetos.h"

using namespace std;

class Minimapa{

private:
	map<Segmento*,Objetos*>* minimapa;


public:

	//EL MINIMAPA ESTA COMPUESTO POR SEGMENTOS QUE SON INTERPERTADOS POR UNA O MAS RECTAS (PUEDEN DEFINIR CURVAS)
	//ES UN CONJUNTO DE SUBSEGMENTOS (LA CLASE SEGMENTOS REPRESENTA ESTOS SUBSEGMENTOS)
	Minimapa();

	void setObjetos(Segmento* seg,Objetos* objetos);
	void setLengthX(int x);
	void setLengthY(int y);

	int getLengthX();
	int getLengthY();

	map<Segmento*,Objetos*>* getMinimapa();

	void getAllPosiciones();

	//Eliminar la memoria pedida por el minimapa
	//Eliminar toda la memoria pedida para los segmentos y los objetos
	~Minimapa();
};




#endif /* MINIMAPA_H_ */
