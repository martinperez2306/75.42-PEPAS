#ifndef SERVIDORBUILDER_H_
#define SERVIDORBUILDER_H_

#include "servidor.h"
#include "pugixml.hpp"
#include <iostream>
#include <string>

#define ZOOM 10
using namespace std;

class ServidorBuilder{

private:
	Servidor* servidor;
	int cantidadDeConexiones;
	int puerto;

public:

	BaseDeDatos* baseDeDatos;
	ServidorBuilder();

	void setServidor(Servidor* servidor);
	Servidor* getServidor();

	Servidor* build();
	Servidor* build(string path);

	void setCantidadDeConexiones(int cantidadDeConexiones);
	void setPuerto(int puerto);

	int getPuerto();
	int getCantidadDeConexiones();

	void parsearXML(const char* archivo);

	bool puertoValido(const char* puertoTxt);

	bool sonDigitos(const char* str);


	//no libera la memoria del servidor. Recordar Eliminarla en el programa principal.
	~ServidorBuilder();
};



#endif /* SERVIDORBUILDER_H_ */
