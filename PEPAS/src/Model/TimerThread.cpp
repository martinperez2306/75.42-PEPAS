//
// Created by arturi on 27/11/17.
//

#include "../../headers/Model/TimerThread.h"

TimerThread::TimerThread(Servidor *sv, bool CerrarServidor) {
    this->srv = sv;
    this->estaCerrado = false;

}

void TimerThread::run() {
    startTime = clock();
    string timeString;
    while (!estaCerrado){
        timeString = this->renderTiempo(startTime);
        srv->setTime(timeString);
    }
}


string TimerThread::renderTiempo(clock_t sTime) {
    int secondsPassed;
    int minutesPassed;
    secondsPassed =  ((clock() - sTime ) / (CLOCKS_PER_SEC));

    minutesPassed = secondsPassed / 60;

    secondsPassed = secondsPassed - (minutesPassed * 60) ;

    string tiempo = to_string((int)minutesPassed) + ":" + to_string((int)secondsPassed);

    return tiempo;
}