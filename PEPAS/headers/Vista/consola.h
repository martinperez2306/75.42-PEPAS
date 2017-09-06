#ifndef CONSOLA_H_
#define CONSOLA_H_

#include <iostream>
#include <string>
#include "../Controller/servidorController.h"
#include <stdlib.h>

using namespace std;

class Consola{

private:
	bool terminado;
	//int numeroPagina;
	ServidorController* servidorController;
	bool esint(std::string entrada);
public:

	Consola();

	void setTerminado(bool terminado);
	bool getTerminado();

	/////////////////Cargar Paginas/////////////////
	void cargarPagina(int numeroPagina);
	void cargarPaginaPrincipal();
	void cargarIngresarUsuario();
	void cargarPaginaCaracteristicasDelServidor();
	void cargarPaginaCrearServidor();
	void cargarCambioLoggeo();

	~Consola();
};


#endif /* CONSOLA_H_ */
