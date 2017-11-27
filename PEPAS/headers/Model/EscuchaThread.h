//
// Created by arturi on 22/09/17.
//

#ifndef SERVIDOR_ESCUCHATHREAD_H
#define SERVIDOR_ESCUCHATHREAD_H


#include "thread.h"
#include "socket.h"
#include "servidor.h"
#include "../Vista/consola.h"

class EscuchaThread : public Thread {
private:
    Socket* socket;
    Servidor* servidor;
    list<ClientesThread> clientThreads;

public:
    EscuchaThread(Servidor* servidor1);
    virtual void run ();


};


#endif //SERVIDOR_ESCUCHATHREAD_H
