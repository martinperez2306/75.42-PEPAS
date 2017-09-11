//
// Created by florencia on 03/09/17.
//

#include "../../headers/com.pepas.view/consola.h"

Consola::Consola(){

    this->terminado = false;
    this->salirMenu = false;
    this->clienteController = new ClienteController();
}

void Consola::setTerminado(bool terminado){

    this->terminado = terminado;
}


bool Consola::getTerminado(){

    return this->terminado;
}

void Consola::cargarPagina() {
    system("clear");
	int numeroPagina;
    while(!this->terminado) {
		cout<<"*********************************************"<<endl;
		cout<<"Ingrese una opcion segun corresponda"<<endl;
		cout<<"Seleccione 1 conectarse al servidor"<<endl;
		cout<<"Seleccione 2 para salir"<<endl;
		cout<<"*********************************************"<<endl;
		cout<<"-->";
		cin>> numeroPagina;
    	switch(numeroPagina) {
			case 1:
				this->clienteController->crearCliente();
				this->clienteController->conectarConElServidor();
				//this->clienteController->cliente->logIn();
				this->cargarMenuPrincipal();
				break;
			default:
				this->clienteController->salirDelPrograma();
				this->terminado = true;
    	}
    }
}


void Consola::cargarMenuPrincipal() {
	while(!this->salirMenu) {
		int numeroPag;
		cout<<"Ingrese una opcion segun corresponda"<<endl;
		cout<<"Seleccione 1 para el Stress Test"<<endl;
		cout<<"Seleccione 2 para el enviar un mensaje de Chat"<<endl;
		cout<<"Seleccione 3 para el enviar un mensaje privado"<<endl;
		cout<<"Seleccione 4 para el enviar un mensaje de prueba"<<endl;
		cout<<"Seleccione 5 para el deslogearse"<<endl;
		cout<<"Cualquier tecla para salir"<<endl;
		cin>> numeroPag;
		switch(numeroPag) {
			case 1:
				this->clienteController->stressTest();
				break;
			case 2:
				this->clienteController->enviarMensajeChat();
				break;
			case 3:
				this->clienteController->enviarMensajePrivado();
				break;
			case 4:
				this->clienteController->mensajeDePrueba();
				break;
			case 5:
				this->clienteController->logOut();
				break;
			default:
				this->salirMenu = true;
		}
	}
	cout<<"Se va a cerrar la conexion con el servidor..."<<endl;
	this->clienteController->desconectarseDelServidor();
	cout<<"Terminando la ejecucion del programa"<<endl;
	this->terminado = true;

}

void Consola::cargarPaginaCrearCliente(){

    cout<<"CREANDO CLIENTE..............."<<endl;

    for(int i = 0;i<10;i++){
        cout<<"."<<endl;
    }
    cout<<"CLIENTE CREADO CORRECTAMENTE"<<endl;
    //this->cargarPaginaCaracteristicasDelCliente();
}


Consola::~Consola(){

    delete this->clienteController;
}

