#include "../../headers/Vista/consola.h"
#include "../../headers/Model/usuario.h"
#include <string>

Consola::Consola(){

	this->terminado = false;
	//this->numeroPagina = 0;
	this->servidorController = new ServidorController();
}

void Consola::setTerminado(bool terminado){

	this->terminado = terminado;
}


bool Consola::getTerminado(){

	return this->terminado;
}

void Consola::cargarPagina(int numeroPagina){
	system("clear");
	switch(numeroPagina){
	case 1:
		this->cargarPaginaCaracteristicasDelServidor();
		break;
	case 2:
		this->terminado = true;
		break;
	default:
		this->cargarPaginaPrincipal();
	}
}
void Consola::cargarPaginaPrincipal(){

	int numeroPagina;
	cout<<"Ingrese una opcion segun corresponda"<<endl;
	cout<<"Seleccione 1 para ir a las caracteristicas del servidor"<<endl;
	cout<<"Seleccione 2 para salir"<<endl;
	cin>> numeroPagina;
	this->cargarPagina(numeroPagina);
}

void Consola::cargarPaginaCaracteristicasDelServidor(){

    char buffer;
	Usuario* usuario = this->servidorController->getUsuario();

	cout<<"La cantidad maxima de conexiones es: "<<this->servidorController->getMaximoClientesServidor()<<endl;
	cout<<"El puerto es: "<<servidorController->getPuertoServidor()<<endl;
	cout<<"Usuario Disponible = "<<usuario->getUsuario()<<" "<<"Contrase�a = "<<usuario->getContrasenia()<<endl;
    buffer = getchar();
}

void Consola::cargarPaginaCrearServidor(){

    char buffer;
	cout<<"CREANDO SERVIDOR..............."<<endl;
	this->servidorController->crearServidor();
	for(int i = 0;i<10;i++){
		cout<<"."<<endl;
	}
	cout<<"SERVIDOR CREADO CORRECTAMENTE"<<endl;
    buffer = getchar();
}



Consola::~Consola(){

	delete this->servidorController;
}

