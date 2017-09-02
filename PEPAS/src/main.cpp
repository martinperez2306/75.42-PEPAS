#include <iostream>
#include "servidorBuilder.h"
using namespace std;

int main() {

	ServidorBuilder* builder = new ServidorBuilder() ;
	Servidor* servidor;

	builder->parsearXML();
	servidor = builder->build();
	cout<<"Se ha creado el servidor, la cantidad maxima de conexiones es: "<<servidor->getCantidadDeConexiones()<<endl;
	cout<<"Se ha creado el servidor y el puerto es:"<<servidor->getPuerto();
	cout<<"Usuario Disponible ="<<servidor->getBaseDeDatos()->getUsuario()->getUsuario()<<" "<<"Contraseña = "<<servidor->getBaseDeDatos()->getUsuario()->getContrasenia()<<endl;
	delete servidor;
	delete builder;
	return 0;
}


