//
// Created by arturi on 18/09/17.
//

#ifndef SERVIDOR_SHUTDOWNTHREAD_H
#define SERVIDOR_SHUTDOWNTHREAD_H


#include "thread.h"
#include "servidor.h"

class ShutdownThread : public Thread {

private:
    bool &quit;
    Servidor* srv;
public:
    ShutdownThread(bool &quit, Servidor* servidor);

    virtual void run();

};


#endif //SERVIDOR_SHUTDOWNTHREAD_H
