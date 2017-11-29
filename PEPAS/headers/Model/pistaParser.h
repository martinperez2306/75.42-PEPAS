#ifndef PISTAPARSER_H_
#define PISTAPARSER_H_

#include "puntero.h"
#include "minimapa.h"
#include "pugixml.hpp"
#include "segmento.h"
#include "Objeto.h"
#include "Mapa.h"

#define RECTO 0
#define CURVAI 1
#define CURVAD -1
#define ARBOL 1

class PistaParser{


//CUIDADO AL ENTENDER COMO ESTA DIVIDIDA LA PISTA (SEGMENTOS, SUBSEGMENTOS Y OBJETOS)

private:

	Puntero* puntero;
	Posicion* posicionActual;
	int generarDireccion(string direccion);
	void girarYAvanzar(string direccion, int distancia,Mapa* mapa);
	void generarObjeto(int distancia,string ladoDelObjeto,pugi::xml_node tipoDeObjeto,Mapa* mapa);


public:

	PistaParser();

	void setPosicionActual(Posicion* posActual);
	Posicion* getPosicionActual();

	Mapa* parsearMapa(const char*);
	Minimapa* getMinimapa();
	Mapa* getMapa();

//Eliminar referencia a puntero solamente (lo demas es usado por el servidor)
	~PistaParser();

};

#endif /* PISTAPARSER_H_ */
