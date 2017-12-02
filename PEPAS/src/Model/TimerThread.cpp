#include <zconf.h>
#include "../../headers/Model/TimerThread.h"

TimerThread::TimerThread(bool CerrarServidor) {

    this->estaCerrado = false;
    this->segundos = 0;
    this->minutos = 0;
    this->empezarAContar = false;
    this->incremento = false;
}

void TimerThread::run() {
    startTime = clock();
    //string timeString;
    while (!estaCerrado){
    	if(this->empezarAContar){
    		if(this->incremento){
    			this->incrementar();
    		}else{
    			this->decrementar();
    		}
    	}
//        time = this->renderTiempo(startTime);
        //srv->setTime(timeString);
    }
}


string TimerThread::renderTiempo(clock_t sTime) {
    float secondsPassed;
    float minutesPassed;
    secondsPassed =  ((clock() - sTime ) / (float)(CLOCKS_PER_SEC));

    minutesPassed = secondsPassed / (float)60;

    secondsPassed = secondsPassed - (minutesPassed * (float)60) ;

    string tiempo = to_string((int)minutesPassed) + ":" + to_string((int)secondsPassed);

    return tiempo;
}

string TimerThread::getTiempo() {
    string time = to_string(this->minutos) + ":" + to_string(this->segundos);
    return time;
}

void TimerThread::stop() {
    this->estaCerrado = true;
}

void TimerThread::frenar(){
	this->empezarAContar = false;
}

void TimerThread::reiniciar() {
    this->segundos = 0;
    this->minutos = 0;
    this->empezarAContar = false;
    this->incremento = false;
}

void TimerThread::setIncremento(bool incremento){
	this->incremento = incremento;
}

void TimerThread::incrementar(){
    this->segundos+= 1;
    if(this->segundos == 60){
    	this->minutos+=1;
    	this->segundos = 0;
    }
    sleep(1);
}

void TimerThread::decrementar(){
    sleep(1);
	this->segundos-= 1;
    if(this->segundos == 0){
    	this->incremento = true;
    }
}

bool TimerThread::getIncremento(){
	return this->incremento;
}

void TimerThread::temporizar(){
	this->segundos = 5;
	this->minutos = 0;
	this->incremento = false;
	this->empezarAContar = true;
}

void TimerThread::cronometrar(){
	this->segundos = 0;
	this->minutos = 0;
	this->incremento = true;
	this->empezarAContar = true;
}

