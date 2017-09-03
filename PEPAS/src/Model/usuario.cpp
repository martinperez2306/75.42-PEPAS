#include "../../headers/Model/usuario.h"

Usuario::Usuario(){
	 this->contrasenia = "";
	 this->usuario = "";
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



