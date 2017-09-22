//
// Created by arturi on 18/09/17.
//

#include "../../headers/Model/ClientesThread.h"

ClientesThread::ClientesThread( Socket* socket, Servidor* server, bool CerrarServidor) : socket(socket), srv(server), estaCerrado(CerrarServidor) {
    borrable = false;
}


void ClientesThread::run() {
    //bool socketEstaCerrado = false;
    cout<<"Thread listo para correr cliente ... "<<endl;
    //while (!estaCerrado) {
        srv->parsearMensaje(srv->recibirMensaje(this->socket));
        string msg = "0010/1/FIUBA/e";
        srv->enviarMensaje(msg, this->socket);
    //}
}

bool ClientesThread::esBorrable() {
    return this->borrable;
}




