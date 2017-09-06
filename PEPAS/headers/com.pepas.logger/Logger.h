/*
 * Logger.h
 *
 *  Created on: 6 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_LOGGER_LOGGER_H_
#define COM_PEPAS_LOGGER_LOGGER_H_

#include <fstream>
#include <string>
#include <iostream>
#include <ctime>

	void crear_logger();
	void cerrar_logger();
	void loggear(std::string mensaje, int prioridad);
	void setNivelLogger(int nivel);

#endif /* COM_PEPAS_LOGGER_LOGGER_H_ */
