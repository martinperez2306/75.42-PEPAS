#ifndef SERVIDORBUILDER_H_
#define SERVIDORBUILDER_H_

#include "servidor.h"
#include "pugixml.hpp"
#include <iostream>
#include <string>

using namespace std;

class ServidorBuilder{

private:
	Servidor* servidor;
	int cantidadDeConexiones;
	int puerto;
	BaseDeDatos* baseDeDatos;

public:
	ServidorBuilder();

	void setServidor(Servidor* servidor);
	Servidor* getServidor();

	Servidor* build();
	Servidor* build(string path);

	void setCantidadDeConexiones(int cantidadDeConexiones);
	void setPuerto(int puerto);

	int getPuerto();
	int getCantidadDeConexiones();

	void parsearXML();

	//no libera la memoria del servidor. Recordar Eliminarla en el programa principal.
	~ServidorBuilder();
};



#endif /* SERVIDORBUILDER_H_ */
