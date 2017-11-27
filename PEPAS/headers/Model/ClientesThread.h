//
// Created by arturi on 18/09/17.
//

#ifndef SERVIDOR_CLIENTESTHREAD_H
#define SERVIDOR_CLIENTESTHREAD_H

#include "thread.h"
#include "servidor.h"
#include "AliveThread.h"
#include "CalculateThread.h"
#include "TimerThread.h"


class ClientesThread : public Thread {
private:
    Socket* socket;
    Servidor* srv;
    bool estaCerrado;
    bool borrable; // para saber si se puede borrar el thread.
    bool inGame;
    bool lanzeCalculoThread;
    AliveThread aliveThread = AliveThread(srv, estaCerrado);
    CalculateThread calculoThread = CalculateThread(srv, estaCerrado, socket);

public:

    ClientesThread(Socket* socket, Servidor* sv, bool CerrarServidor);

    virtual void run();

    bool esBorrable();

};



#endif //SERVIDOR_CLIENTESTHREAD_H
