#include "baseDeDatos.h"

BaseDeDatos::BaseDeDatos(){

	this->usuario = NULL;
}

/*list<Usuario*>* BaseDeDatos::getUsuarios(){

	return this->usuarios;
}*/

void BaseDeDatos::setUsuario(Usuario* usuario){
	this->usuario = usuario;
}

Usuario* BaseDeDatos::getUsuario(){
	return this->usuario;
}

/*void BaseDeDatos::agregarUsuarioABaseDeDatos(Usuario* usuario){
	this->usuarios->push_back(usuario);
}*/

BaseDeDatos::~BaseDeDatos(){

	delete this->usuario;
}


