#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "baseDeDatos.h"
#include "socket.h"



class Servidor{

private:
	int puerto;
	int cantidadDeConexiones;
	int socketEscucha;
	BaseDeDatos* baseDeDatos;
	Socket serverSocket;
	string ip;

public:
	Servidor();

	void setPuerto(int puerto);

	int getPuerto();

	void setCantidadDeConexiones(int cantidadDeConexiones);

	int getCantidadDeConexiones();

	void setBaseDeDatos(BaseDeDatos* baseDeDatos);

	Socket getSocket();

	int getSocketEscucha();

	void iniciarServidor();

	BaseDeDatos* getBaseDeDatos();

	~Servidor();

	string getIP();
};


#endif /* SERVIDOR_H_ */
