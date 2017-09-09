#include "../../headers/Model/baseDeDatos.h"


typedef pair<string, Usuario*> user;

BaseDeDatos::BaseDeDatos(){

	this->usuarios = new map<string,Usuario*>;
}


Usuario* BaseDeDatos::getUsuario(string username){
	return this->usuarios->find(username)->second;
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
}


