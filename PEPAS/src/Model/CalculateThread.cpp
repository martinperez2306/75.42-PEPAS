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
    	this->srv->actualizarEstadoDeCarrera((int)this->Automovil->getPosition() / 200);
    	if(!this->srv->carreraHaTerminado()){
    	int curve = srv->curvaEnKilometraje((int)(Automovil->getPosition()/200));
    	string msg = Automovil->calculateMove(curve);
        string playersInformation = srv->actualizarJuego(Automovil);
        if (srv->hayColision())
            stringACrear = Automovil->procesarMovimiento() + playersInformation;
        else stringACrear = msg + playersInformation;
        unsigned long largoDelMensaje = stringACrear.length();
        stringProcesado = this->srv->agregarPadding(largoDelMensaje) + stringACrear;
        usleep (4000);
        cout<<stringProcesado<<endl;
        this->srv->enviarMensaje(stringProcesado,socket);
<<<<<<< HEAD
    	}
=======
>>>>>>> ad752e90955bb95b576e30ccce9493c3f460484d
    }
}

void CalculateThread::terminar() {
    estaCerrado = true;
}

void CalculateThread::agregarGrisado() {
    string player = (this->srv->obtenerGrisados().front());
    cout<<this->srv->obtenerGrisados().size()<<endl;
    cout<<"jugador grisado "<<player<<endl;
    this->srv->obtenerAutoConId(player)->setJugador(5);
}
