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
    ClienteParser::SocketData sd = this->clienteParser->parsearXML((char*)"cliente.xml");
    this->socketData = sd;
}

void ClienteController::asignarServidor(){
    // que hace exactamente?

}


void ClienteController::conectarConElServidor(){
    this->cliente->conectarseAlServidor((string) socketData.ip, socketData.puerto);


}

void ClienteController::mensajeDePrueba(){
    this->cliente->enviarMensajePrueba();
}

void ClienteController::desconectarseDelServidor(){

}


void ClienteController::logIn(string nomrbe, string contrasenia){

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
