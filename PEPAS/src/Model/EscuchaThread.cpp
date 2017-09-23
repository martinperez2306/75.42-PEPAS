//
// Created by arturi on 22/09/17.
//

#include "../../headers/Model/EscuchaThread.h"

void EscuchaThread::run() {
    servidor->iniciarServidor();
    while(!servidor->getTerminado()){
        cout << "la wea" << endl;
        this->socket = servidor->aceptarConexiones();
        for (auto it = clientThreads.begin(); it != clientThreads.end();
             ++it) {
            if (it->esBorrable()) {
                it->join();
                it = clientThreads.erase(it);
            }
        }

        clientThreads.emplace_back(this->socket, this->servidor, this->servidor->getTerminado());
        /*Se obtiene el ultimo de la pila y se lo ejecuta con start()*/
        clientThreads.back().start();
    }

    /*Cierro todas las conexiones abiertas*/
    //servidor->cerrarSockets();


    /*Limpio threads*/
    for (auto it = clientThreads.begin(); it != clientThreads.end(); ++it){
        (*it).join();
    }

}


EscuchaThread::EscuchaThread(Servidor *servidor1) :  servidor(servidor1)  {

}
