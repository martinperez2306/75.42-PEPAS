//
// Created by florencia on 03/09/17.
//

#include "../../headers/com.pepas.controllers/clienteController.h"
#include "../../headers/com.pepas.parser/ClienteParser.h"


ClienteController::ClienteController(){}

ClienteController::ClienteController(ClienteParser *clientePaser) {
	this->clienteParser = clientePaser;
}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)

void ClienteController::crearCliente(){

    this->cliente= new Cliente();
    //a penas crea el cliente se empieza a parsear el achivo xml
    this->clienteParser->parsearXML((char*)"cliente.xml");
}

void ClienteController::asignarServidor(){
    // que hace exactamente?

}


void ClienteController::conectarConElServidor(){
    const char* ip = this->clienteParser->getIp();
    int puerto = this->clienteParser->getPuerto();
    this->cliente->conectarseAlServidor((string) ip, puerto);


}

void ClienteController::mensajeDePrueba(){
    this->cliente->enviarMensajePrueba();
}

void ClienteController::desconectarseDelServidor(){

}


void ClienteController::logIn(char* nomrbe, char* contrasenia){

}

void ClienteController::logOut() {

}


void ClienteController::stressTest(){
}

void ClienteController::enviarMensajeChat(){

}

void ClienteController::enviarMensajePrivado(){

}

void ClienteController::salirDelPrograma() {
	//chequear que este desconectado, sino, desconectar
	cout<<"SALISTE DEL CHAT"<<endl;
}

ClienteController::~ClienteController(){
    delete this->cliente;
}
