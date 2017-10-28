#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/Recta.h"
Recta::Recta(){
	this->a = 0;
	this->b = 0;
	this->x = 0;
	this->y = 0;

}

void Recta::calcularEcuacionDeLaRecta(int x0,int y0, int x1, int y1){

	int deltaX = (x1-x0);
	int deltaY = (y1-y0);

	if(deltaX == 0 || deltaY == 0){
		//RECTAS NO DIAGONALES
		if(deltaX == 0){
			this->x = x0;
		}
		if(deltaY == 0){
			this->a = 0;
			this->b = y0;
		}
		}else{
		//RECTAS DIAGONALES
		int pendiente = (deltaY / deltaX);
		this->a = pendiente;
		this->b = (y0 - x0*pendiente);
		}
}

int Recta::calcularY(int x){
	return ((this->a*x) + this->b);
}

Recta::~Recta() {
	// TODO Auto-generated destructor stub
}


