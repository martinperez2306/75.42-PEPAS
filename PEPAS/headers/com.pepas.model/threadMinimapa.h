//
// Created by arturi on 18/09/17.
//
#ifndef COM_PEPAS_MODEL_THREADMINIMAPA_H_
#define COM_PEPAS_MODEL_THREADMINIMAPA_H_

#include "thread.h"
#include "cliente.h"


class threadMinimapa : public Thread {
private:
    Cliente* cliente;

public:

    //recvThread(Cliente* cliente);

    threadMinimapa(Cliente* cliente);

    threadMinimapa();


    virtual void run();


};

#endif

