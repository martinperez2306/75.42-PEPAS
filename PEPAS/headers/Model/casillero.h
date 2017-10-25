#ifndef CASILLERO_H_
#define CASILLERO_H_

#define VACIO 0
#define PISTA 1
#define ARBOL 2



class Casillero{

private:
	int pista;
	int arbol;
	int cartel;

public:
	Casillero();

	void setPista();
	void setArbol();
	void setCartel(int velocidadMaxima);
	//por las dudas...
	void setArbol(int arbol);
	void setPista(int pista);

	int getPista();
	int getArbol();
	int getCartel();

	~Casillero();
};




#endif /* CASILLERO_H_ */
