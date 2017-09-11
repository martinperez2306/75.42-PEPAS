#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "baseDeDatos.h"
#include "socket.h"
#include <string>



class Servidor{

private:
	int puerto;
	int cantidadDeConexiones;
	BaseDeDatos* baseDeDatos;
	int socketEscucha;
	Socket* serverSocket;
	


public:
	Servidor();

	void setPuerto(int puerto);
	int getPuerto();

	void setCantidadDeConexiones(int cantidadDeConexiones);
	int getCantidadDeConexiones();

	void setBaseDeDatos(BaseDeDatos* baseDeDatos);
	BaseDeDatos* getBaseDeDatos();

	void mostrarUsuariosDisponibles();

	string getIP();
	int obtenerSocketFD();

	void iniciarServidor();
	void aceptarConexiones();
	void finalizarConexiones();
	void cerrarSockets();
	void parsearMensaje(std::string mensaje);

	Socket* obtenerSocket();



	~Servidor();


	void asignarSocketFd(int crear);
};


#endif /* SERVIDOR_H_ */
