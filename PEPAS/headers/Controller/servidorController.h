#ifndef SERVIDORCONTROLLER_H_
#define SERVIDORCONTROLLER_H_

#include"../Model/servidor.h"
#include"../Model/servidorBuilder.h"
#include "../Model/ClientesThread.h"


#include <iostream>
using namespace std;
class ServidorController{


private:
	Servidor* servidor;
	ServidorBuilder* servidorBuilder;


public:



	ServidorController();

	void crearServidor(const char* archivo);

	void mostrarUsuariosDisponibles();

	int getPuertoServidor();

	int getMaximoClientesServidor();

	Usuario* getUsuario(string username);

	~ServidorController();


    void mostrarUsuariosConectados();


	Servidor* obtenerServidor();
};



#endif /* SERVIDORCONTROLLER_H_ */
