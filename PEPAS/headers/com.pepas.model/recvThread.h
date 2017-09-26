//
// Created by arturi on 18/09/17.
//
#ifndef COM_PEPAS_MODEL_RECVTHREAD_H_
#define COM_PEPAS_MODEL_RECVTHREAD_H_

#include "thread.h"
#include "cliente.h"


class recvThread : public Thread {
private:
    Cliente* cliente;

public:

    //recvThread(Cliente* cliente);

    recvThread(Cliente* cliente);

    recvThread();


    virtual void run();


};

#endif
