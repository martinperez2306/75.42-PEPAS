#ifndef ZOOMER_H_
#define ZOOMER_H_

#define INFINITO 2147483647

#include "Mapa.h"
#include "minimapa.h"
#include "World.h"
#include "Recorredor.h"

#define PADDING 100

class Zoomer {

private:
	//Rellenar la matriz con los valores de los segmentos aumentados
	void aumentar(int x, int y,int pendiente,Mapa* mapa);
	//Aplicar el multiplicador a un segmento
	Segmento* zoomRuta(Segmento* segmento);
	Objeto* zoomObjeto(Objeto* objeto);
	int tamanioZoom;

public:
	Zoomer();

	//El tamaño del sum es un multiplicador x1,x2,x10,
	//Para aumentar se multiplica, para disminuir se divide
	void setTamanioZoom(int tamanioZoom);
	int getTamanioZoom();
	//Expander los segmentos a lo ancho
	void zoomMinimapToMap(Minimapa* minimapa, Mapa* mapa);
	//Achicar los segmentos del mapa para minimapa
	void zoomMapToMinimap(Mapa* mapa,Minimapa* minimapa);
	//Crear el mundo a traves del mapa
	void zoomMapToWorld(Mapa* mapa, World* world);
	void zoomMapToMinimap(Mapa* mapa, Minimapa* minimapa,Recorredor* recorredor);
	//Agregar paddings para evitar conflictos
	void agregarPaddingToWorld(World* world, int metrosFinales);
	void agregarPaddingToRecorredor(Recorredor* recorredor);
	~Zoomer();
};

#endif /* ZOOMER_H_ */
