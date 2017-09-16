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
	//int socketEscucha;
	Socket* serverSocket;
	int conexiones;
	int socketFD2;

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

	int getSocketFD2();
	void setSocketFD2(int fd2);

	void iniciarServidor();
	void aceptarConexiones();
	void finalizarConexiones();
	void cerrarSockets();
	void parsearMensaje(std::string mensaje);
	std::string recibirMensaje();

	Socket* obtenerSocket();

	void mostrarUsuariosConectados();
	BaseDeDatos* obtenerBaseDeDatos();

	~Servidor();


    void validarCliente(string basic_string, string basicString);
};


#endif /* SERVIDOR_H_ */
