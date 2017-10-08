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
    loggear (msglogger,2);
    aliveThread.start();
    loggear ("aliveThread corriendo ...",3);
    while (!estaCerrado) {
        string msg = srv->parsearMensaje(srv->recibirMensaje(this->socket), this->socket);
        aliveThread.asignarContador(srv->obtenerAlive());
        if (msg == "CerrarCliente"){
            borrable=true;
            aliveThread.cerrarContador();
            break;
        }
    }
    aliveThread.join();
}

bool ClientesThread::esBorrable() {
    return this->borrable;
}






