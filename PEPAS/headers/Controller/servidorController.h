#ifndef SERVIDORCONTROLLER_H_
#define SERVIDORCONTROLLER_H_

#include"../Model/servidor.h"
#include"../Model/servidorBuilder.h"


class ServidorController{


private:
	Servidor* servidor;
	ServidorBuilder* servidorBuilder;

public:
	ServidorController();

	void crearServidor();

	int getPuertoServidor();

	int getMaximoClientesServidor();

	Usuario* getUsuario();

	~ServidorController();

};



#endif /* SERVIDORCONTROLLER_H_ */
