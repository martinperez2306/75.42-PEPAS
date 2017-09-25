//
// Created by arturi on 18/09/17.
//

#include "../../headers/com.pepas.model/recvThread.h"

recvThread::recvThread( Cliente* cliente) : cliente(cliente) {
    this->cliente = cliente;
}


void recvThread::run() {

    while (cliente->estalogueado()) {
        cliente->parsearMensaje(cliente->recibirMensaje());
    }
}





