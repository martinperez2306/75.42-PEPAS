//
// Created by florencia on 03/09/17.
//

#include "../../headers/com.pepas.view/consola.h"

enum { STATE_SEND, STATE_RECV } state = STATE_SEND;

int socketFD;
Socket *socketCliente;
ClienteController *controller;
bool salirMenu = false;
bool terminado = false;
pthread_t _send, _recv;

Consola::Consola(){
    this->clienteController = new ClienteController();
}

void* mostrarMensajes(void* threadid) {
	cout<<"estoy escuchando mensajes..."<<endl;
	string mensaje = socketCliente->Recibir(socketFD, BUFLEN);
	if(mensaje != "") {
		cout<< "Nuevo mensaje: " << mensaje <<endl;
	}
}

void cargarMenuPrincipal() {
	while(!salirMenu) {
		int numeroPag;
		cout<<"*********************************************"<<endl;
		cout<<"Ingrese una opcion segun corresponda"<<endl;
		cout<<"Seleccione 1 para el Stress Test"<<endl;
		cout<<"Seleccione 2 para el enviar un mensaje de Chat"<<endl;
		cout<<"Seleccione 3 para el enviar un mensaje privado"<<endl;
		cout<<"Seleccione 4 para el enviar un mensaje de prueba"<<endl;
		cout<<"Seleccione 5 para el deslogearse"<<endl;
		cout<<"Cualquier tecla para salir"<<endl;
		cout<<"*********************************************"<<endl;
		cin>> numeroPag;
		switch(numeroPag) {
			case 1:
				controller->stressTest();
				break;
			case 2:
				controller->enviarMensajeChat();
				break;
			case 3:
				controller->enviarMensajePrivado();
				break;
			case 4:
				controller->mensajeDePrueba();
				break;
			case 5:
				controller->logOut();
				break;
			default:
				salirMenu = true;
		};
	}
	cout<<"Se va a cerrar la conexion con el servidor..."<<endl;
	controller->desconectarseDelServidor();
	cout<<"Terminando la ejecucion del programa"<<endl;
	terminado = true;

}

void* enviarMensajes(void* threadid) {

	cargarMenuPrincipal();
}

void *Consola::cargarPagina() {
	int numeroPagina;
    while(!terminado) {
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
				if (this->clienteController->conectarConElServidor() == -1) {
					cout<<"Ocurrio un error al intentar conectarse, intente nuevamente"<<endl;
				} else {
                    cout<<"Haciendo cambio de puerto"<<endl;
					this->clienteController->obtengoPuertoNuevoYHagoConectar();
					this->clienteController->obtenerCliente()->logIn();
					socketFD = this->clienteController->cliente->obtenerSocketFD();
					controller = this->clienteController;
					socketCliente = this->clienteController->cliente->obtenerSocket();
					pthread_create(&_send, NULL, enviarMensajes, NULL);
					pthread_create(&_recv, NULL, mostrarMensajes, NULL);

					pthread_join(_send, NULL);
					pthread_join(_recv,NULL);
				}
				break;
			default:
				this->clienteController->salirDelPrograma();
				terminado = true;
    	}
    }
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

