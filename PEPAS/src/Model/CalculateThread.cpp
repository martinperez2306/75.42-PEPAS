//
// Created by arturi on 06/11/17.
//

#include <zconf.h>
#include "../../headers/Model/CalculateThread.h"

CalculateThread::CalculateThread(Servidor *sv, bool CerrarServidor, Socket* socket) {
    this->srv = sv;
    this->estaCerrado = false;
    this->socket = socket;


}

void CalculateThread::run() {
    string stringACrear, stringProcesado;
    this->user = this->srv->obtenerUsuarioConFd(this->socket->obtenerPuerto());
    this->Automovil = this->srv->obtenerAutoConId(user);
    while (!estaCerrado){
    	int curve = srv->curvaEnKilometraje((int)(Automovil->getPosition()/200));
    	string msg = Automovil->calculateMove(curve);
        string playersInformation = srv->actualizarJuego(Automovil);
        stringACrear = msg + playersInformation;
        unsigned long largoDelMensaje = stringACrear.length();
        stringProcesado = this->srv->agregarPadding(largoDelMensaje) + stringACrear;
        usleep (4000);
        this->srv->enviarMensaje(stringProcesado,socket);
        cout<<stringProcesado<<endl;
    }
}

void CalculateThread::terminar() {
    estaCerrado = true;
}
