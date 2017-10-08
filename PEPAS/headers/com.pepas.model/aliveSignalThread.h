//
// Created by arturi on 07/10/17.
//

#ifndef CLIENTE_ALIVESINGNALTHREAD_H
#define CLIENTE_ALIVESINGNALTHREAD_H


#include "cliente.h"
#include "thread.h"

class aliveSignalThread : public Thread {
private:
    Cliente* cliente;

public:

    //recvThread(Cliente* cliente);

    explicit aliveSignalThread(Cliente* cliente);

    aliveSignalThread();


    virtual void run();
};





#endif //CLIENTE_ALIVESINGNALTHREAD_H
