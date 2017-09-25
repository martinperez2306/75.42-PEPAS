#include "../../headers/com.pepas.view/consola.h"

enum { STATE_SEND, STATE_RECV } state = STATE_SEND;

int socketFD;
Socket *socketCliente;
ClienteController *controller;

pthread_t _send, _recv;

Consola::Consola(){
   this->clienteController = new ClienteController();
   terminado = false;
}

void* mostrarMensajes(void* threadid) {
	cout<<"estoy escuchando mensajes..."<<endl;
	string mensaje = socketCliente->Recibir(socketFD, BUFLEN);
	if(mensaje != "") {
		cout<< "Nuevo mensaje: " << mensaje <<endl;
	}
}

void Consola::cargarMenuPrincipal() {
	while(!terminado) {
		int numeroPag;
		cout<<"*********************************************"<<endl;
		cout<<"Ingrese una opcion segun corresponda"<<endl;
		cout<<"Seleccione 1 para loguearse"<<endl;
		cout<<"Seleccione 2 para el enviar un mensaje de Chat"<<endl;
		cout<<"Seleccione 3 para el enviar un mensaje privado"<<endl;
		cout<<"Seleccione 4 para el enviar un mensaje de prueba"<<endl;
		cout<<"Seleccione 5 para el Stress Test"<<endl;
		cout<<"Seleccione 6 para el deslogearse"<<endl;
		cout<<"Cualquier tecla para salir"<<endl;
		cout<<"*********************************************"<<endl;
		cin>> numeroPag;
		switch(numeroPag) {
			case 1:
			{
				controller->obtenerCliente()->logIn();
				if (controller->obtenerCliente()->estalogueado()){
					controller->empezarRecibir();
				}
			}
				break;
			case 2:
				//controller->enviarMensajeChat();
                controller->entrarAlChat();
				break;
			case 3:
				controller->enviarMensajePrivado();
				break;
			case 4:
				controller->mensajeDePrueba();
				break;
			case 5:
				controller->stressTest();
				break;
			case 6:
				controller->logOut();
				break;
			default:
				terminado = true;
		};
	}
	cout<<"Se va a cerrar la conexion con el servidor..."<<endl;
	controller->desconectarseDelServidor();
	cout<<"Terminando la ejecucion del programa"<<endl;

}

void* enviarMensajes(void* threadid) {

	//cargarMenuPrincipal();
}

void *Consola::cargarPagina() {
	
	int numeroPagina;
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
				socketFD = this->clienteController->obtenerCliente()->obtenerSocketFD();
				controller = this->clienteController;
				socketCliente = this->clienteController->obtenerCliente()->obtenerSocket();
				this->cargarMenuPrincipal();
				
				
			}
			break;
		case 2:
		{
			this->clienteController->salirDelPrograma();
			terminado = true;				
		}
			break;
		default:{
			cout << "Opcion incorrecta" << endl;
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

bool Consola::terminoConsola(){
	return this->terminado;
}

ClienteController* Consola::getController(){
	return this->clienteController;
}