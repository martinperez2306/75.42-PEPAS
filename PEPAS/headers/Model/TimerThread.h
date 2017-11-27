//
// Created by arturi on 27/11/17.
//

#ifndef SERVIDOR_TIMERTHREAD_H
#define SERVIDOR_TIMERTHREAD_H


#include "thread.h"
#include "servidor.h"

class TimerThread : public Thread {
private:
    Servidor* srv;
    bool estaCerrado;
    clock_t startTime;

public:

    TimerThread(Servidor* sv, bool CerrarServidor);

    virtual void run();

    string renderTiempo(clock_t sTime);


};


#endif //SERVIDOR_TIMERTHREAD_H
