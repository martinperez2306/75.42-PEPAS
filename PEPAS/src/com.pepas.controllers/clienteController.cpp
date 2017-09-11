//
// Created by florencia on 03/09/17.
//

#include "../../headers/com.pepas.controllers/clienteController.h"
#include "../../headers/com.pepas.parser/ClienteParser.h"


ClienteController::ClienteController(){
	this->socketData.ip = "127.0.0.1"; //TODO HARDCODEEEEEEE
	this->socketData.puerto = 27015;  //TODO HARDCODEEEEEEE

}

ClienteController::ClienteController(ClienteParser *clientePaser) {
	this->clienteParser = clientePaser;
}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)

void ClienteController::crearCliente(){

    this->cliente= new Cliente();
    //a penas crea el cliente se empieza a parsear el achivo xml
    //ClienteParser::SocketData sd = this->clienteParser->parsearXML((char*)"../75.42-PEPAS/PEPAS/src/com.pepas.parser/cliente.xml");
    //this->socketData = sd;
}

void ClienteController::asignarServidor(){
    // que hace exactamente?

}


void ClienteController::conectarConElServidor(){
    this->cliente->conectarseAlServidor(socketData.ip, socketData.puerto);


}

void ClienteController::mensajeDePrueba(){
}

void ClienteController::desconectarseDelServidor(){

}


void ClienteController::logOut() {

}


void ClienteController::stressTest(){
}

void ClienteController::enviarMensajeChat(){
	string texto;
	cout<<"Ingresa el mensaje: "<<endl;
	cin >> texto;
	Mensaje *mensaje = new Mensaje(Mensaje::BROADCAST_MSG, texto, Mensaje::BROADCAST);
	//this->cliente->enviarMensaje(mensaje->toSrvText()); //TODO EEEEEEEEEEEEEEee
}

void ClienteController::enviarMensajePrivado(){
	string texto;
	int user;
	cout<<"Ingresa el mensaje: "<<endl;
	cin >> texto;
	cout<<"Ingresa el ususario destino: "<<endl;
	cin >> user;
	Mensaje *mensaje = new Mensaje(Mensaje::PRIVATE_MSG, texto, user);
	this->cliente->enviarMensaje(mensaje->toSrvText());
}

void ClienteController::salirDelPrograma() {
	//chequear que este desconectado, sino, desconectar
	cout<<"SALISTE DEL CHAT"<<endl;
}

ClienteController::~ClienteController(){
    delete this->cliente;
}
