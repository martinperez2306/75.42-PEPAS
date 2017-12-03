//
// Created by arturi on 20/09/17.
//

#include "../../headers/Vista/ConsolaThread.h"

ConsolaThread::ConsolaThread(Consola *consol) : consola(consol){

}

void ConsolaThread::run() {

    while(!consola->getTerminado()){
        consola->cargarPagina(0);
    }

}