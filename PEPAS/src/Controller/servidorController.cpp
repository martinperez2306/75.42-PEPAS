#include "../../headers/Controller/servidorController.h"
#include "../../headers/Model/logger.h"


ServidorController::ServidorController() {
	loggear("Entro al contructor de ServidorController",2);
	this->servidor = NULL;
	this->servidorBuilder = NULL;
	loggear("Salio contructor de ServidorController",2);
	loggear (" ",2);
}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)
void ServidorController::crearServidor(){

	loggear("Entro al crearServidor",2);
	this->servidorBuilder = new ServidorBuilder();
	this->servidorBuilder->parsearXML();
	this->servidor = this->servidorBuilder->build();
	delete servidorBuilder;
	loggear("salio del crearServidor",2);
	loggear (" ",2);
}

void ServidorController::mostrarUsuariosDisponibles(){

	this->servidor->mostrarUsuariosDisponibles();
}
int ServidorController::getMaximoClientesServidor(){

	return this->servidor->getCantidadMaximaDeConexiones();
}

int ServidorController::getPuertoServidor(){

	return this->servidor->getPuerto();
}

Usuario* ServidorController::getUsuario(string username){
	return this->servidor->getBaseDeDatos()->getUsuario(username);
}

void ServidorController::mostrarUsuariosConectados(){
	this->servidor->mostrarTodosLosUsuariosConectados();
}

ServidorController::~ServidorController(){
	delete this->servidor;
}


Servidor* ServidorController::obtenerServidor(){
    return this->servidor;
}

