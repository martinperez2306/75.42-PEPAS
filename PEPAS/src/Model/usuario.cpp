#include "../../headers/Model/usuario.h"

Usuario::Usuario(){
	this->contrasenia = "contraseña vacia";
	this->usuario = "usuario vacio";
	this->socketFD = NULL;
	this->conectado = true;
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

bool Usuario::estaConectado() {
	return this->conectado;
}



