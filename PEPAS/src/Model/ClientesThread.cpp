//
// Created by arturi on 18/09/17.
//

#include "../../headers/Model/ClientesThread.h"
#include "../../headers/Model/logger.h"

ClientesThread::ClientesThread( Socket* socket, Servidor* server, bool CerrarServidor) : socket(socket), srv(server), estaCerrado(CerrarServidor) {
    borrable = false;
}


void ClientesThread::run() {
    //bool socketEstaCerrado = false;
    string msglogger = "Thread listo para correr cliente ... ";
    loggear (msglogger,1);
    while (!estaCerrado) {
        string msg = srv->parsearMensaje(srv->recibirMensaje(this->socket), this->socket);
        if (msg == "CerrarCliente"){
            borrable=true;
            break;
        }

        //srv->enviarMensaje(msg, this->socket);
    }
}

bool ClientesThread::esBorrable() {
    return this->borrable;
}




