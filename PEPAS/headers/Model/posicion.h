#ifndef POSICION_H_
#define POSICION_H_

class Posicion{

private:
	int x;
	int y;

public:

	Posicion();
	Posicion(int x, int y);

	void setX(int x);
	void setY(int y);

	int getX();
	int getY();

	~Posicion();
};



#endif /* POSICION_H_ */
