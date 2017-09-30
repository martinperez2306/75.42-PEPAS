//
// Created by arturi on 18/09/17.
//

#include "../../headers/com.pepas.model/recvThread.h"

/*
recvThread::recvThread( Cliente* cliente) : cliente(cliente) {
    this->cliente = cliente;
}
*/


void recvThread::run() {

    while (cliente->estaConectado()) {
        cliente->parsearMensaje(cliente->recibirMensaje());
    }
}

recvThread::recvThread(Cliente* cliente) {
    this->cliente = cliente;
}

/*NO BORRAR*/
recvThread::recvThread() {}







