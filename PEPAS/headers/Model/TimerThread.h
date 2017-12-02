#ifndef SERVIDOR_TIMERTHREAD_H
#define SERVIDOR_TIMERTHREAD_H


#include "thread.h"


class TimerThread : public Thread {
private:

    bool estaCerrado;
    clock_t startTime;
    string time;

    int segundos;
    int minutos;

    bool empezarAContar;
    bool incremento;

public:

    TimerThread(bool CerrarServidor);

    virtual void run();

    string renderTiempo(clock_t sTime);

    string getTiempo();


    void stop();

    void frenar();

    void reiniciar();

    void setIncremento(bool incremento);

    void incrementar();

    void decrementar();

    bool getIncremento();

    void temporizar();

    void cronometrar();
};


#endif //SERVIDOR_TIMERTHREAD_H
