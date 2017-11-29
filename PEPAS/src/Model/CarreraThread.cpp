#include "../../headers/Model/CarreraThread.h"

CarreraThread::CarreraThread(bool estaCerrado) {
	this->estaCerrado = estaCerrado;
}

void CarreraThread::setServidor(Servidor* servidor){
	this->servidor = servidor;
}

void CarreraThread::run(){
	while(!this->estaCerrado){
		if(this->servidor->carreraGlobalHaTerminado()){
			this->servidor->enviarMensajeCambioDePista();
			this->servidor->cambiarDePista();
            cout<<"CAMBIO de pista"<<endl;
		}
	}
}

void CarreraThread::terminar(){
	this->estaCerrado = true;
}
