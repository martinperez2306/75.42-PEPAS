#include "../../headers/Model/CarreraThread.h"

CarreraThread::CarreraThread(bool estaCerrado) {
	this->estaCerrado = estaCerrado;
}

void CarreraThread::setServidor(Servidor* servidor){
	this->servidor = servidor;
}

void CarreraThread::run(){
	while(!this->estaCerrado){
		if(this->servidor->carreraHaTerminado()){
			this->servidor->enviarMensajeCambioDePista();
			this->servidor->cambiarDePista();
		}
	}
}

void CarreraThread::terminar(){
	this->estaCerrado = true;
}
