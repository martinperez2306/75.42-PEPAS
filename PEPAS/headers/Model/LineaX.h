#ifndef HEADERS_MODEL_LINEAX_H_
#define HEADERS_MODEL_LINEAX_H_

#include <map>

using namespace std;

class LineaX {

private:
	//Mapa<posicionX,contenido de la posicion>
	//Tamaño 7 --> 2 fuera de pista || 3 pista || 2 fuera de pista
	map<int,int>* lineaX;
	// si el tramo en x de ese kilometraje corresponde a una curva o a una recta
	//1: Curva izquierda || 0: Recta || -1: Curva Derecha
	int curva;

public:
	//construir mapa
	LineaX();

	void setLinea(map<int,int> lineaX);
	void agregarElemento(int posicionX,int elemento);
	void inicializarLinea();
	void setCurva(int curva);
	int obtenerElemento(int posicionX);
	int getCurva();

	//destruir la referencia al mapa
	~LineaX();
};

#endif /* HEADERS_MODEL_LINEAX_H_ */
