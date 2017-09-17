#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "baseDeDatos.h"
#include "socket.h"
#include <string>
#include "thread.h"


class Servidor{

private:
	int puerto;
	int cantidadDeConexiones;
	BaseDeDatos* baseDeDatos;
	//int socketEscucha;
	Socket* serverSocket;
	Socket* serverSocket2;
	int conexiones;
	int socketFD2;
	int puerto2;
	int socketFD;



	//FUNCIONES ESTATICAS PARA LOS THREADS DEL SERVIDOR
	static void *IniciarConexiones(void* servidor);
	static void *IniciarConexiones2(void* servidor);

public:
	Servidor();

	Socket* obtenerSocket2();
	int getPuerto2();

	void setSocketFD(int fd);
	int getSocketFD();

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

	//HARCODEADAS PARA PROBAR THREADS//
	void iniciarServidor2();
	void aceptarConexiones2();

	void finalizarConexiones();
	void cerrarSockets();
	void parsearMensaje(std::string mensaje);
	std::string recibirMensaje();

	Socket* obtenerSocket();

	void mostrarUsuariosConectados();
	BaseDeDatos* obtenerBaseDeDatos();

	void abrirConexiones();


	~Servidor();


    void validarCliente(string basic_string, string basicString);
};


#endif /* SERVIDOR_H_ */
