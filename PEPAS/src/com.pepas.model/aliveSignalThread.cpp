//
// Created by arturi on 07/10/17.
//

#include <zconf.h>
#include "../../headers/com.pepas.model/aliveSignalThread.h"


aliveSignalThread::aliveSignalThread(Cliente *cliente) {
    this->cliente = cliente;

}

void aliveSignalThread::run() {

    while (cliente->estaConectado()) {
        int signalActual = cliente->obtenerAliveCounter();
        string msg = "0009/7/signal";
       // cliente->enviarMensaje(msg);
        sleep (4);
        if (cliente->obtenerAliveCounter() == signalActual){
            cout <<"**** Se detecto problemas en la conexion de red ****"<<endl;
            this->cliente->grisarAuto();
            //cliente->parsearMensaje("0005");
            //break;
        } else {
            this->cliente->noGrisarAuto();
        }

    }
}

aliveSignalThread::aliveSignalThread() {

}
