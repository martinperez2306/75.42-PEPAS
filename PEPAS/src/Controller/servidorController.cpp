#include "../../headers/Controller/servidorController.h"


ServidorController::ServidorController(){

	this->servidor = NULL;
	this->servidorBuilder = NULL;
}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)
void ServidorController::crearServidor(){

	this->servidorBuilder = new ServidorBuilder();
	this->servidorBuilder->parsearXML();
	this->servidor = this->servidorBuilder->build();
	delete servidorBuilder;
}

void ServidorController::mostrarUsuariosDisponibles(){

	this->servidor->mostrarUsuariosDisponibles();
}
int ServidorController::getMaximoClientesServidor(){

	return this->servidor->getCantidadDeConexiones();
}

int ServidorController::getPuertoServidor(){

	return this->servidor->getPuerto();
}

Usuario* ServidorController::getUsuario(string username){

	return this->servidor->getBaseDeDatos()->getUsuario(username);
}

ServidorController::~ServidorController(){
	delete this->servidor;
}

