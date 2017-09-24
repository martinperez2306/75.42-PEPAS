#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_


#include <list>
#include "usuario.h"
#include <map>
#include <iomanip>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

class BaseDeDatos{

private:
	map<string,Usuario*>* usuarios;
	map<string,Usuario*>::iterator iterador;

	map<string,Usuario*>* usuariosConectados;



public:
	BaseDeDatos();

	Usuario* getUsuario(string username);

	void agregarUsuarioABaseDeDatos(Usuario* usuario);

	//bool validarDatosDeUsuario(string username);

	void mostrarTodosLosUsuarios();

	int obtenerSocketUsuario (string usuario);

	map<string, Usuario *> * obtenerMapUsuarios();

	//DEBE ELIMINAR LA MEMORIA PEDIDA PARA CADA USUARIO EN LA BASE DE DATOS (CREADA POR EL BUILDER).
	~BaseDeDatos();



	Usuario* getUsuarioConectado(string username);

	void agregarUsuarioConectadoABaseDeDatos(string nombre);

	void mostrarTodosLosUsuariosConectados();


	int obtenerSocketUsuarioConectado(string usuario);

	map<string, Usuario *> * obtenerMapUsuariosConectados();


};



#endif /* BASEDEDATOS_H_ */