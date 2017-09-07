//
// Created by florencia on 03/09/17.
//

#include "../../headers/com.pepas.controllers/clienteController.h"


ClienteController::ClienteController(){

}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)

void ClienteController::crearCliente(){

    //this->servidorBuilder = new ServidorBuilder();
    //this->servidorBuilder->parsearXML();
    // En que parte hacemos el parseo del cliente?
    this->cliente= new Cliente();
    //delete servidorBuilder;
}

void ClienteController::asignarServidor() {}


void ClienteController::conectarConElServidor(){

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
