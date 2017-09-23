//
// Created by florencia on 03/09/17.
//

#include "../../headers/com.pepas.controllers/clienteController.h"
#include "../../headers/com.pepas.parser/ClienteParser.h"


ClienteController::ClienteController(){
//	this->socketData.ip = "127.0.0.2"; //TODO HARDCODEEEEEEE
//	this->socketData.puerto = 27015;  //TODO HARDCODEEEEEEE
//	this->socketData.puerto2 = 8010; //TODO HARDCODEEEEEEE
	this->socketData = this->clienteParser->parsearXML("cliente.xml");
}

ClienteController::ClienteController(ClienteParser *clientePaser) {
	this->clienteParser = clientePaser;
}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)

void ClienteController::crearCliente(){

    this->cliente= new Cliente();
    //a penas crea el cliente se empieza a parsear el achivo xml
    //ClienteParser::SocketData sd = this->clienteParser->parsearXML((char*)"../75.42-PEPAS/PEPAS/src/com.pepas.parser/cliente.xml");
    //ClienteParser::SocketData sd = this->clienteParser->parsearXML((char*)"src/com.pepas.parser/cliente.xml");
    //this->socketData = sd;
}

void ClienteController::asignarServidor(){
    // que hace exactamente?

}


int ClienteController::conectarConElServidor(){
    return this->cliente->conectarseAlServidor(socketData.ip, socketData.puerto);
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
    string mensajeProcesado, bug, texto;
	string destinatario = "";
	cout<<this->obtenerCliente()->obtenerUsuario()->getNombre()<<" ingresa el mensaje: ";
	//TODO aca hay un bug que no lo entiendo, si no pongo las variables de esta forma anda mal.
	getline(cin, bug);
	getline(cin, texto);
	Mensaje *mensaje = new Mensaje(Mensaje::BROADCAST_MSG, texto, this->obtenerCliente()->obtenerUsuario()->getNombre(), destinatario);
    mensajeProcesado = this->obtenerCliente()->procesarMensaje(mensaje);
	this->obtenerCliente()->enviarMensaje(mensajeProcesado);
}

void ClienteController::enviarMensajePrivado(){
	string texto, mensajeProcesado, destinatario, bug;
    cout<<this->obtenerCliente()->obtenerUsuario()->getNombre()<<" ingresa el mensaje: ";
	//TODO aca hay un bug que no lo entiendo, si no pongo las variables de esta forma anda mal.
	getline (cin,bug);
	getline(cin, texto);
	cout<<"Ingresa el ususario destino: ";
	cin >> destinatario;
	Mensaje *mensaje = new Mensaje(Mensaje::PRIVATE_MSG, texto, this->obtenerCliente()->obtenerUsuario()->getNombre(), destinatario);
	mensajeProcesado = this->obtenerCliente()->procesarMensaje(mensaje); //mensaje->toSrvText()
    this->obtenerCliente()->enviarMensaje(mensajeProcesado);

}

void ClienteController::salirDelPrograma() {
	//chequear que este desconectado, sino, desconectar
	cout<<"SALISTE DEL CHAT"<<endl;
}

ClienteController::~ClienteController(){
    delete this->cliente;
}

Cliente *ClienteController::obtenerCliente() {
    return this->cliente;
}


void ClienteController::obtengoPuertoNuevoYHagoConectar() {
	/*Recibo 4 bytes en donde ya se que voy a recibir 4 bytes con el puerto nuevo*/
	string puerto = this->obtenerCliente()->obtenerSocket()->Recibir(this->obtenerCliente()->obtenerSocketFD(), 4);
	/*Cierro la conexion con el puerto del xml*/
    cout<<"El puerto recibido es: "<<puerto<<endl;
	this->obtenerCliente()->obtenerSocket()->CerrarConexion(this->obtenerCliente()->obtenerSocketFD());

	/*Seteo mi nuevo puerto*/
	this->socketData.puerto= stoi(puerto,nullptr,10);
	/*Me conecto al nuevo servidor*/
	this->obtenerCliente()->conectarseAlServidor(socketData.ip, socketData.puerto);
	cout<<"Conectado satisfactorio con puerto: "<<socketData.puerto<<endl;

}
