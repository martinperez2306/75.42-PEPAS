#include "consola.h"
#include "usuario.h"

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
	system("cls");
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

	Usuario* usuario = this->servidorController->getUsuario();

	cout<<"La cantidad maxima de conexiones es: "<<this->servidorController->getMaximoClientesServidor()<<endl;
	cout<<"El puerto es: "<<servidorController->getPuertoServidor()<<endl;
	cout<<"Usuario Disponible = "<<usuario->getUsuario()<<" "<<"Contraseña = "<<usuario->getContrasenia()<<endl;
	system("pause");
}

void Consola::cargarPaginaCrearServidor(){

	cout<<"CREANDO SERVIDOR..............."<<endl;
	this->servidorController->crearServidor();
	for(int i = 0;i<10;i++){
		cout<<"."<<endl;
	}
	cout<<"SERVIDOR CREADO CORRECTAMENTE"<<endl;
	system("pause");
}



Consola::~Consola(){

	delete this->servidorController;
}

