//
// Created by arturi on 20/09/17.
//

#ifndef SERVIDOR_CONSOLATHREAD_H
#define SERVIDOR_CONSOLATHREAD_H


#include "../../headers/Model/thread.h"
#include "../../headers/Vista/consola.h"

class ConsolaThread : public Thread {
private:
    Consola* consola;
public:
    ConsolaThread(Consola* consol);
    virtual void run();

};


#endif //SERVIDOR_CONSOLATHREAD_H
