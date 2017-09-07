//
// Created by florencia on 03/09/17.
//

#include "../../headers/com.pepas.controllers/clienteController.h"


ClienteController::ClienteController(){}

ClienteController::ClienteController(ClienteParser *clientePaser) {
	this->clienteParser = clientePaser;
}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)

void ClienteController::crearCliente(){

    this->cliente= new Cliente();
}

void ClienteController::asignarServidor() {}


void ClienteController::conectarConElServidor(){
	//crear socket

}

void ClienteController::desconectarseDelServidor(){

}

void ClienteController::logIn(){

}

void ClienteController::stressTest(){

}

void ClienteController::enviarMensajeChat(){

}

void ClienteController::enviarMensajePrivado(){

}

ClienteController::~ClienteController(){
    delete this->cliente;
}
