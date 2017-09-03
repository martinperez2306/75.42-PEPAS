#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_


#include <list>
#include "usuario.h"

using namespace std;

class BaseDeDatos{

private:
	Usuario* usuario;

public:
	BaseDeDatos();

	void setUsuario(Usuario* usuario);

	Usuario* getUsuario();

	//void agregarUsuarioABaseDeDatos(Usuario* usuario);

	//DEBE ELIMINAR LA MEMORIA PEDIDA PARA CADA USUARIO EN LA BASE DE DATOS (CREADA POR EL BUILDER).
	~BaseDeDatos();

};



#endif /* BASEDEDATOS_H_ */
