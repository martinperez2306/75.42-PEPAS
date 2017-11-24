#include "../../headers/com.pepas.model/threadMinimapa.h"

/*
recvThread::recvThread( Cliente* cliente) : cliente(cliente) {
    this->cliente = cliente;
}
*/


void threadMinimapa::run() {

    while (cliente->estaConectado()){
        if(cliente->estalogueado()&&cliente->minimapaEstaCompleto()){
        	cliente->graficarMinimapa();
        }
    }
}

threadMinimapa::threadMinimapa(Cliente* cliente) {
    this->cliente = cliente;
}

/*NO BORRAR*/
threadMinimapa::threadMinimapa() {}



