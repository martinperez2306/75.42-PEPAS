#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/threadMinimapa.h"

/*
recvThread::recvThread( Cliente* cliente) : cliente(cliente) {
    this->cliente = cliente;
}
*/


void threadMinimapa::run() {

    while (cliente->estaConectado()) {
        cliente->graficarMinimapa();

    }
}

threadMinimapa::threadMinimapa(Cliente* cliente) {
    this->cliente = cliente;
}

/*NO BORRAR*/
threadMinimapa::threadMinimapa() {}



