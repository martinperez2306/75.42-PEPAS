//
// Created by florencia on 03/09/17.
//

#include "consola.h"

Consola::Consola(){

    this->terminado = false;
    //this->numeroPagina = 0;
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
            this->clienteController->enviarMensajePrivado();
            break;
        default:
            this->cargarPaginaPrincipal();
    }
}
void Consola::cargarPaginaPrincipal(){

    int numeroPagina;
    cout<<"Ingrese una opcion segun corresponda"<<endl;
    cout<<"Seleccione 1 para ir a las caracteristicas del cliente"<<endl;
    cout<<"Seleccione 2 para salir"<<endl;
    cin>> numeroPagina;
    this->cargarPagina(numeroPagina);
}

void Consola::cargarPaginaCaracteristicasDelCliente(){
    int numeroPag;
    cout<<"Ingrese una opcion segun corresponda"<<endl;
    cout<<"Seleccione 3 para conectar con el servidor"<<endl;
    cout<<"Seleccione 4 para desconectarse del servidor"<<endl;
    cout<<"Seleccione 5 para hacer Log In"<<endl;
    cout<<"Seleccione 6 para el Stress Test"<<endl;
    cout<<"Seleccione 7 para el enviar un mensaje de Chat"<<endl;
    cout<<"Seleccione 8 para el enviar un mensaje privado"<<endl;
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

