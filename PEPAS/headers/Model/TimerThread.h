#ifndef SERVIDOR_TIMERTHREAD_H
#define SERVIDOR_TIMERTHREAD_H


#include "thread.h"


class TimerThread : public Thread {
private:

    bool estaCerrado;
    clock_t startTime;
    string time;

public:

    TimerThread(bool CerrarServidor);

    virtual void run();

    string renderTiempo(clock_t sTime);

    string getTiempo();


};


#endif //SERVIDOR_TIMERTHREAD_H
