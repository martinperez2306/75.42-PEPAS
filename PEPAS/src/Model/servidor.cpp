#include "../../headers/Model/servidor.h"
#include "../../headers/Model/baseDeDatos.h"
#include "../../headers/Model/socket.h"



Servidor::Servidor(){

	this->cantidadDeConexiones = 0;
	this->puerto = 0;
	this->baseDeDatos = NULL;
    this->ip = '127.0.0.1';


};

int Servidor::getCantidadDeConexiones(){

	return this->cantidadDeConexiones;
}

int Servidor::getPuerto(){

	return this->puerto;
}

void Servidor::setCantidadDeConexiones(int cantidadDeConexiones){

	this->cantidadDeConexiones = cantidadDeConexiones;
}

void Servidor::setPuerto(int puerto){

	this->puerto = puerto;
}

void Servidor::setBaseDeDatos(BaseDeDatos* baseDeDatos){
	this->baseDeDatos = baseDeDatos;
}

BaseDeDatos* Servidor::getBaseDeDatos(){
	return this->baseDeDatos;
}


//DEBE BORRAR LA MEMORIA QUE PIDIO EL BUILDER PARA LA BASE DE DATOS.
Servidor::~Servidor(){

	delete this->baseDeDatos;
}


Socket Servidor::getSocket() {
    return this->serverSocket;
}

int Servidor::getSocketEscucha() {
    return this->socketEscucha;
}

string Servidor::getIP() {
    return this->ip;
}



void Servidor::iniciarServidor() {
    int listenSock = this->getSocketEscucha();
    Socket svSocket = this->getSocket();
    int maxConexiones = getCantidadDeConexiones();
    int svPuerto = this->getPuerto();
    string svIP = this->getIP();

    listenSock = svSocket.Crear(); //devuelve el file descriptor
    svSocket.Enlazar(listenSock, svPuerto,svIP);
    svSocket.Escuchar(listenSock, maxConexiones);
}

