#include <zconf.h>
#include "../../headers/Model/CalculateThread.h"

CalculateThread::CalculateThread(Servidor *sv, bool CerrarServidor, Socket* socket) {
    this->srv = sv;
    this->estaCerrado = false;
    this->socket = socket;
    this->primeroE1 = true;
    this->primeroE2 = true;
    this->primeroE3 = true;
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
            usleep (5000);
            cout<<stringProcesado<<endl;
            this->srv->enviarMensaje(stringProcesado,socket);
        } else {
            if(this->Automovil->getEtapa() == 1) {
                if(this->primeroE1) {
                    cout<<"ganador etapa 1 es: " << this->Automovil->obtenerPlayer() << endl;
                    this->Automovil->setScoreEtapa1(100000);
                    this->primeroE1 = false;
                }
            }
            if(this->Automovil->getEtapa() == 2) {
                if(this->primeroE2) {
                    cout<<"ganador etapa 2 es: " << this->Automovil->obtenerPlayer() << endl;
                    this->Automovil->setScoreEtapa2(100000);
                    this->primeroE2 = false;
                }
            }
            if(this->Automovil->getEtapa() == 3) {
                if(this->primeroE3) {
                    cout<<"ganador etapa 3 es: " << this->Automovil->obtenerPlayer() << endl;
                    this->Automovil->setScoreEtapa3(100000);
                    this->primeroE3 = false;
                }
            }
        }
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
