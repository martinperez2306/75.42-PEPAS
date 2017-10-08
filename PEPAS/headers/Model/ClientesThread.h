//
// Created by arturi on 18/09/17.
//

#ifndef SERVIDOR_CLIENTESTHREAD_H
#define SERVIDOR_CLIENTESTHREAD_H

#include "thread.h"
#include "servidor.h"
#include "AliveThread.h"


class ClientesThread : public Thread {
private:
    Socket* socket;
    Servidor* srv;
    bool estaCerrado;
    bool borrable; // para saber si se puede borrar el thread.
    AliveThread aliveThread = AliveThread(srv, estaCerrado);
public:

    ClientesThread(Socket* socket, Servidor* sv, bool CerrarServidor);

    virtual void run();

    bool esBorrable();

};



#endif //SERVIDOR_CLIENTESTHREAD_H
