#ifndef MAPA_H_
#define MAPA_H_

#include <iostream>

using namespace std;

class Mapa {

private:
	int** mapa;
	int lengthX;
	int lengthY;
	void inicializarMapa();
public:
	Mapa(int lengthX,int lengthY);
	void mostrarMapa();
	void setPos(int x, int y,int value);
	int getPos(int x,int y);
	~Mapa();
};

#endif /* MAPA_H_ */
