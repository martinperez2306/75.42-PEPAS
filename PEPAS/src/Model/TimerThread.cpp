#include "../../headers/Model/TimerThread.h"

TimerThread::TimerThread(bool CerrarServidor) {

    this->estaCerrado = false;

}

void TimerThread::run() {
    startTime = clock();
    //string timeString;
    while (!estaCerrado){
        time = this->renderTiempo(startTime);
        //srv->setTime(timeString);
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

string TimerThread::getTiempo() {
    return time;
}
