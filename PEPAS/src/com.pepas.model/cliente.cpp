#include "../../headers/com.pepas.model/cliente.h"


Cliente::Cliente() {
    this->socketCliente = new Socket();
    this->socketFD=0;

}

void Cliente::logIn(){
    string usuario;
    string clave;
    cout<<"Ingrese su nombre de usuario"<<endl;
    cin>> usuario;
    cout<<"Ingrese su clave"<<endl;
    cin>> clave;
    this->usuario->setearNombre(usuario);
    this->usuario->setearContrasenia(clave);
}

void Cliente::conectarseAlServidor(string ip, int puerto) {
    asignarSocketFd(obtenerSocket()->Crear());
    this->obtenerSocket()->Conectar(obtenerSocketFD(), puerto, ip);
    cout <<"Conectado satisfactorio"<< endl;

}


void Cliente::enviarMensaje(string mensaje){

/*    send (socketCliente, (char *)&mensaje, sizeof (mensaje), 0);
    unsigned Rta;
    recv (socketCliente, (char *)&Rta, sizeof (Rta), 0);
    printf ("Dato enviado: %u, Respuesta recibida: %u\n", mensaje, Rta);*/
}

void Cliente::desconectarseDelServidor() {
    //neesito ver lo del servidor?
}


Cliente::~Cliente() {

}

void Cliente::asignarSocketFd(int socket) {
    this->socketFD=socket;

}

int Cliente::obtenerSocketFD() {
    return socketFD;
}

Socket* Cliente::obtenerSocket() {
        return this->socketCliente;

}
