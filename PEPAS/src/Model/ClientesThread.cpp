//
// Created by arturi on 18/09/17.
//

#include "../../headers/Model/ClientesThread.h"

ClientesThread::ClientesThread( int socket, Servidor* server) : socketFD(socket), srv(server) {
    borrable = false;
}


void ClientesThread::run() {
    cout<<"laconcha detumadre"<<endl;
    srv->asignarSocketFD(socketFD);
    srv->parsearMensaje(srv->recibirMensaje());

}

