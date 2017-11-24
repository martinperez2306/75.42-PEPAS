#ifndef RECTA_H_
#define RECTA_H_

#include <iostream>

using namespace std;

class Recta {

private:
	int y;
	int x;
	int a;
	int b;

public:
	Recta();

	void calcularEcuacionDeLaRecta(int x0,int y0, int x1, int y1);
	int calcularY(int x);
	~Recta();

	//GETTERS AND SETTERS
	int getA() {
		return a;
	}

	void setA(int a) {
		this->a = a;
	}

	int getB() {
		return b;
	}

	void setB(int b) {
		this->b = b;
	}

	int getX() {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() {
		return y;
	}

	void setY(int y){
		this->y = y;
	}
};


#endif /* RECTA_H_ */
