#ifndef PISTAPARSER_H_
#define PISTAPARSER_H_

#include "puntero.h"
#include "minimapa.h"
#include "pugixml.hpp"
#include "segmento.h"
#include "objetos.h"
#include "Objeto.h"
#include "Mapa.h"

class PistaParser{


	//CUIDADO AL ENTENDER COMO ESTA DIVIDIDA LA PISTA (SEGMENTOS, SUBSEGMENTOS Y OBJETOS)

private:

	Mapa* mapa;
	Minimapa* minimapa;
	Puntero* puntero;
	Posicion* posicionActual;
	int generarDireccion(string direccion);
	void girarYAvanzar(string direccion, int distancia);
	void generarObjeto(int distancia,string ladoDelObjeto,pugi::xml_node tipoDeObjeto);


public:

	PistaParser();

	void setPosicionActual(Posicion* posActual);
	Posicion* getPosicionActual();

	void parsearMapa();
	Minimapa* getMinimapa();
	Mapa* getMapa();

	void prueba();

	//Eliminar referencia a puntero solamente (lo demas es usado por el servidor)
	~PistaParser();

};

#endif /* PISTAPARSER_H_ */
