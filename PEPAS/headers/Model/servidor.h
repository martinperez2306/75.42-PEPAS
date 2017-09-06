#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "baseDeDatos.h"
#include "socket.h"



class Servidor{

private:
	int puerto;
	int cantidadDeConexiones;
	BaseDeDatos* baseDeDatos;


public:
	Servidor();

	void setPuerto(int puerto);
	int getPuerto();

	void setCantidadDeConexiones(int cantidadDeConexiones);
	int getCantidadDeConexiones();

	void setBaseDeDatos(BaseDeDatos* baseDeDatos);
	BaseDeDatos* getBaseDeDatos();

	~Servidor();


};


#endif /* SERVIDOR_H_ */
