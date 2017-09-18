//
// Created by arturi on 18/09/17.
//

#ifndef SERVIDOR_CLIENTESTHREAD_H
#define SERVIDOR_CLIENTESTHREAD_H

#include "thread.h"
#include "servidor.h"


class ClientesThread : public Thread {
private:
    int socketFD;
    Servidor* srv;
    bool &estaCerrado;
    bool borrable; // para saber si se puede borrar el thread.
public:

    ClientesThread(int socket, Servidor* sv, bool &CerrarServidor);

    virtual void run();

    bool esBorrable();

};



#endif //SERVIDOR_CLIENTESTHREAD_H
