#include <fstream>
#include <string> 
#include <iostream> 
#include <ctime>
#include "logger.h"
using namespace std; 

void loggear(string mensaje, int nivel, int prioridad){

	if(nivel < prioridad)
		return;

	ofstream logger("log.txt",ios::app);

	logger << mensaje << endl;
	logger.close();
}

void iniciar_logger(){

	ofstream logger("log.txt",ios::app);
	time_t current_time;

   struct tm * time_info;

   char timeString[9];
   //string horario =  "Hora:" + timeString;

   time(&current_time);
   time_info = localtime(&current_time);
   strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

   logger << "**********************************************************************************************************************************" << endl;
   logger << " " << endl;
   logger << "Inicio del logueo" << endl;
   logger << "Hora: ";
   logger << timeString << endl;
   logger << " " << endl;
   logger << "**********************************************************************************************************************************" << endl;
   logger.close();

}


