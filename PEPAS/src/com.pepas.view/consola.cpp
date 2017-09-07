//
// Created by florencia on 03/09/17.
//

#include "../../headers/com.pepas.view/consola.h"

Consola::Consola(){

    this->terminado = false;
    this->clienteController = new ClienteController();
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
            this->cargarPaginaCrearCliente();
            //aca tambien le tiene que decir al controller que conecte con el servidor
            this->cargarPaginaCaracteristicasDelCliente();
            break;
        case 2:
            this->terminado = true;
            break;
        case 3:
            this->clienteController->conectarConElServidor();
            break;
        case 4:
            this->clienteController->desconectarseDelServidor();
            break;
        case 5:
            this->clienteController->logIn();
            break;
        case 6:
            this->clienteController->stressTest();
            break;
        case 7:
            this->clienteController->enviarMensajeChat();
            break;
        case 8:
            this->clienteController->mensajeDePrueba();
            break;
        default:
            this->cargarPaginaPrincipal();
    }
}
void Consola::cargarPaginaPrincipal(){

    int numeroPagina;
    cout<<"Ingrese una opcion segun corresponda"<<endl;
    cout<<"Seleccione 1 conectarse al servidor"<<endl;
    cout<<"Seleccione 2 para salir"<<endl;
    cin>> numeroPagina;
    this->cargarPagina(numeroPagina);
}

void Consola::cargarPaginaCaracteristicasDelCliente(){
    int numeroPag;
    cout<<"Ingrese una opcion segun corresponda"<<endl;
    cout<<"Seleccione 3 para desconectarse del servidor"<<endl;
    cout<<"Seleccione 4 para hacer Log In"<<endl;
    cout<<"Seleccione 5 para el Stress Test"<<endl;
    cout<<"Seleccione 6 para el enviar un mensaje de Chat"<<endl;
    cout<<"Seleccione 7 para el enviar un mensaje privado"<<endl;
    cout<<"Seleccione 8 para el enviar un mensaje de prueba"<<endl;
    cin>> numeroPag;
    this->cargarPagina(numeroPag);

}

void Consola::cargarPaginaCrearCliente(){

    cout<<"CREANDO CLIENTE..............."<<endl;
    this->clienteController->crearCliente();
    for(int i = 0;i<10;i++){
        cout<<"."<<endl;
    }
    cout<<"CLIENTE CREADO CORRECTAMENTE"<<endl;
}


Consola::~Consola(){

    delete this->clienteController;
}

