//
// Created by arturi on 06/11/17.
//

#ifndef SERVIDOR_CALCULATETHREAD_H
#define SERVIDOR_CALCULATETHREAD_H


#include "thread.h"
#include "servidor.h"

class CalculateThread  : public Thread{
private:
    Socket* socket;
    Servidor* srv;
    bool estaCerrado;
    string user;
    Auto* Automovil;


public:

    CalculateThread(Servidor* sv, bool CerrarServidor, Socket* socket);

    virtual void run();

    //bool esBorrable();

    void terminar();
};



#endif //SERVIDOR_CALCULATETHREAD_H
