
#include "../../headers/com.pepas.logger/Logger.h"

using namespace std;
int LOG_LEVEL;

void crear_logger() {
   LOG_LEVEL = 1;

   ofstream logger("log.txt",ios::app);

   std::time_t timeT = std::time(nullptr);
   std::string timeString = std::asctime(std::localtime(&timeT));

   logger << "**********************************************************************************************************************************" << endl;
   logger << " " << endl;
   logger << "Inicio del logueo:" << endl;
   logger << "Hora: ";
   logger << timeString << endl;
   logger << " " << endl;
   logger << "**********************************************************************************************************************************" << endl;
   logger.close();
}
void loggear(std::string mensaje, int prioridad){


	if(LOG_LEVEL < prioridad)
		return;

	ofstream logger("log.txt",ios::app);

	logger << mensaje << endl;
	logger.close();
}

void setNivelLogger(int nivel){

   LOG_LEVEL = nivel;
}


void cerrar_logger(){

   ofstream logger("log.txt",ios::app);

   std::time_t timeT = std::time(nullptr);
   std::string timeString = std::asctime(std::localtime(&timeT));

   logger << "**********************************************************************************************************************************" << endl;
   logger << " " << endl;
   logger << "Fin del logueo:" << endl;
   logger << "Hora: ";
   logger << timeString << endl;
   logger << " " << endl;
   logger << "**********************************************************************************************************************************" << endl;
   logger.close();

}
