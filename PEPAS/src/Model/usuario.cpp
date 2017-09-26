#include "../../headers/Model/usuario.h"

Usuario::Usuario(){
	this->contrasenia = "contraseña vacia";
	this->usuario = "usuario vacio";
	this->socketFD = NULL;
	this->conectado = false;
}

Usuario::Usuario(string usuario,string contrasenia){

	this->usuario = usuario;
	this->contrasenia = contrasenia;

}

void Usuario::setUsuario(string usuario){

	this->usuario = usuario;
}

void Usuario::setContrasenia(string contrasenia){

	this->contrasenia = contrasenia;
}

string Usuario::getContrasenia(){
	return this->contrasenia;
}

string Usuario::getUsuario(){
	return this->usuario;
}

int Usuario::obtenerSocket() {
	return this->socketFD;
}

void Usuario::estaConectado() {
	this->conectado=true;
}

bool Usuario::getConectado() {
	return this->conectado;
}

void Usuario::asignarSocket(Socket* Socketusuario) {
	this->socket = Socketusuario;
}

Socket *Usuario::getSocket() {
	return this->socket;
}

void Usuario::estaDesconectado() {
    this->conectado=false;
}



