#ifndef PISTAPARSER_H_
#define PISTAPARSER_H_

#include "puntero.h"
#include "minimapa.h"
#include "pugixml.hpp"
#include "segmento.h"
#include "objetos.h"

class PistaParser{


	//CUIDADO AL ENTENDER COMO ESTA DIVIDIDA LA PISTA (SEGMENTOS, SUBSEGMENTOS Y OBJETOS)

private:

	Minimapa* minimapa;
	Puntero* puntero;
	Posicion* posicionActual;
	int generarDireccion(string direccion);
	void girarYAvanzar(string direccion, int distancia,Objetos* objetos);
	void generarObjetos(Objetos* objetos, string ladoDeLosObjetos,pugi::xml_node objeto);


public:

	PistaParser();

	void setPosicionActual(Posicion* posActual);
	Posicion* getPosicionActual();

	void parsearMinimapa();
	Minimapa* getMinimapa();

	void prueba();

	~PistaParser();

};

#endif /* PISTAPARSER_H_ */
