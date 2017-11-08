#ifndef HEADERS_MODEL_LINEAX_H_
#define HEADERS_MODEL_LINEAX_H_

#include <map>

using namespace std;

class LineaX {

private:
	// si el tramo en x de ese kilometraje corresponde a una curva o a una recta
	//1: Curva izquierda || 0: Recta || -1: Curva Derecha
	int curva;

public:
	//construir mapa
	LineaX();

	void setCurva(int curva);
	int getCurva();

	//destruir la referencia al mapa
	~LineaX();
};

#endif /* HEADERS_MODEL_LINEAX_H_ */
