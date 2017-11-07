//
// Created by arturi on 07/10/17.
//


#include <zconf.h>
#include "../../headers/Model/AliveThread.h"
#include "../../headers/Model/logger.h"

AliveThread::AliveThread(Servidor *sv, bool CerrarServidor){
    this->srv = sv;
    this->estaCerrado = CerrarServidor;
    this->contador = 0;

}


void AliveThread::run(){
    bool estaCableado = true;

    while (estaCableado && !estaCerrado){
        int valorActual = contador;
        sleep (5);
        if (valorActual == contador) {
            //estaCableado = false;
            loggear("----->ERROR, Se desconecto el cable", 1);
            cout<<"****Se detecto desconexion de red****"<<endl;
           // srv->cerrarSockets();
        }
    }
}

void AliveThread::asignarContador(int i) {
    this->contador = i;
}

void AliveThread::cerrarContador() {
    this->estaCerrado=true;
}
