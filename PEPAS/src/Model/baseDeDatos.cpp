#include "../../headers/Model/baseDeDatos.h"
#include "../../headers/Model/logger.h"


typedef pair<string, Usuario*> user;

BaseDeDatos::BaseDeDatos(){
	loggear ("Entro al constructor de BaseDeDatos",2);
	this->usuarios = new map<string,Usuario*>;
	this->usuariosConectados = new map<string,Usuario*>;
	loggear ("Salio del constructor de BaseDeDatos",2);
	loggear (" ",2);

}


Usuario* BaseDeDatos::getUsuario(string username){
	Usuario* user ;
	if (this->usuarios->find(username) == this->usuarios->end()){
		user = NULL;
	} else
		user = this->usuarios->find(username)->second;
	return user;
}

void BaseDeDatos::agregarUsuarioABaseDeDatos(Usuario* usuario){

	this->usuarios->insert(user(usuario->getUsuario(),usuario));

}

void BaseDeDatos::mostrarTodosLosUsuarios(){

	for (iterador = usuarios->begin(); iterador != usuarios->end(); ++iterador){
	    cout<< iterador->first << " => " <<"username "<< (iterador->second)->getUsuario() << endl;
		cout<< iterador->first << " => " <<"password "<< (iterador->second)->getContrasenia() << endl;
	}
}

/*bool BaseDeDatos::validarDatosDeUsuario(string username){

	this->iterador= this->usuarios->find(username);
	return (this->iterador != this->usuarios->end());
}*/

BaseDeDatos::~BaseDeDatos(){

	//Borrar cada usuario Creado por el srvBuilder
	for (iterador =usuarios->begin(); iterador != usuarios->end(); ++iterador){
	    delete iterador->second;
	}
	delete this->usuarios;
	//Borrar cada usuario conectado
	for (iterador =usuariosConectados->begin(); iterador != usuariosConectados->end(); ++iterador){
		delete iterador->second;
	}
	delete this->usuariosConectados;
}

int BaseDeDatos::obtenerSocketUsuario(string usuario) {
	return getUsuario(usuario)->obtenerSocket();
}

map<string, Usuario *> * BaseDeDatos::obtenerMapUsuarios() {
	return this->usuarios;
}

////////////////////////////////////para conectados//////////////////

Usuario* BaseDeDatos::getUsuarioConectado(string username){
	Usuario* user ;
	if (this->usuariosConectados->find(username) == this->usuariosConectados->end()){
		user = NULL;
	} else
		user = this->usuariosConectados->find(username)->second;
	return user;
}

void BaseDeDatos::agregarUsuarioConectadoABaseDeDatos(string nombre){
	Usuario* usuario= this->usuarios->at(nombre);

	this->usuariosConectados->insert(user(usuario->getUsuario(),usuario));
}

void BaseDeDatos::mostrarTodosLosUsuariosConectados(){

	for (iterador = usuariosConectados->begin(); iterador != usuariosConectados->end(); ++iterador){
		cout<< iterador->first << " => " <<"username "<< (iterador->second)->getUsuario() << endl;
	}
}


int BaseDeDatos::obtenerSocketUsuarioConectado(string usuario) {
	return getUsuarioConectado(usuario)->obtenerSocket();
}

map<string, Usuario *> * BaseDeDatos::obtenerMapUsuariosConectados() {
	return this->usuariosConectados;
}

void BaseDeDatos::sacarUsuarioConectadoABaseDeDatos(string nombre) {
	this->usuariosConectados->erase(nombre);
}
