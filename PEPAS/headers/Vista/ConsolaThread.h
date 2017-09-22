//
// Created by arturi on 20/09/17.
//

#ifndef SERVIDOR_CONSOLATHREAD_H
#define SERVIDOR_CONSOLATHREAD_H


#include "../Model/thread.h"
#include "consola.h"

class ConsolaThread : public Thread {
private:
    Consola* consola;
public:
    ConsolaThread(Consola* consol);
    virtual void run();

};


#endif //SERVIDOR_CONSOLATHREAD_H
