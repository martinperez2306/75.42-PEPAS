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
	int getSocketEscucha();
	int getCantidadDeConexiones();
	string getIP();

	void setCantidadDeConexiones(int cantidadDeConexiones);
	void setBaseDeDatos(BaseDeDatos* baseDeDatos);
	void iniciarServidor();

	Socket getSocket();
	BaseDeDatos* getBaseDeDatos();

	~Servidor();


};


#endif /* SERVIDOR_H_ */
