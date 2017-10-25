#ifndef ZOOMER_H_
#define ZOOMER_H_

#define INFINITO 2147483647

#include "Mapa.h"
#include "minimapa.h"
#include "Recta.h"

class Zoomer {

private:
	//Rellenar la matriz con los valores de los segmentos aumentados
	void zoom(Mapa* mapa, Segmento* segmento, Objetos* objetos);
	void aumentar(int x, int y,int pendiente,Mapa* mapa);
	int tamanioZoom;
	Recta* recta;

public:
	Zoomer();

	void setTamanioZoom(int tamanioZoom);
	int getTamanioZoom();
	//Expander los segmentos a lo ancho
	void zoomMinimapToMap(Minimapa* minimapa, Mapa* mapa);
	~Zoomer();
};

#endif /* ZOOMER_H_ */
