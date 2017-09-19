//
// Created by arturi on 18/09/17.
//

#include "../../headers/Model/ClientesThread.h"

ClientesThread::ClientesThread( int socket, Servidor* server, bool &CerrarServidor) : socketFD(socket), srv(server), estaCerrado(CerrarServidor) {
    borrable = false;
}


void ClientesThread::run() {
    //bool socketEstaCerrado = false;
    cout<<"Thread listo para correr cliente ... "<<endl;
   /* srv->asignarSocketFD(socketFD);
    while (!borrable) {
        srv->parsearMensaje(srv->recibirMensaje());
        string msg = "0009/1/dale/e";
        srv->enviarMensaje(msg);
    }*/
}

bool ClientesThread::esBorrable() {
    return this->borrable;
}




