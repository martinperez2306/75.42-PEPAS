//
// Created by arturi on 07/10/17.
//
#ifndef SERVIDOR_ALIVETHREAD_H
#define SERVIDOR_ALIVETHREAD_H

#include "thread.h"
#include "servidor.h"

class AliveThread : public Thread {
private:
    Servidor* srv;
    bool estaCerrado;
    int contador;
public:

    AliveThread(Servidor* sv, bool CerrarServidor);

    virtual void run();


    void asignarContador(int i);

    void cerrarContador();
};



#endif //SERVIDOR_ALIVETHREAD_H
