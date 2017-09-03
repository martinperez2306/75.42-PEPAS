/*
 * usuario.h
 *
 *  Created on: 1 sep. 2017
 *      Author: martin
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include <string>
using namespace std;

class Usuario{


private:
	string usuario;
	string contrasenia;

public:

	Usuario();

	Usuario(string usuario, string contrasenia);

	void setUsuario(string usuario);

	void setContrasenia(string contrasenia);

	string getUsuario();

	string getContrasenia();
};




#endif /* USUARIO_H_ */