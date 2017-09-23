#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "baseDeDatos.h"
#include "socket.h"
#include <list>
#include <string>
#include <unordered_map>



class Servidor{

private:
	int puerto;
	int cantidadDeConexiones;
	BaseDeDatos* baseDeDatos;
	int socketEscucha;
	Socket* serverSocket;
	int conexiones;
	int socketFD;
	std::list<int> puertosDisponibles;
	std::list<int> puertosEnUso;
	std::unordered_map<int,int> mapFD; // <puerto, socketFD>
	bool terminado;
	Socket* iniciarConexion(int puerto);




	//FUNCIONES ESTATICAS PARA LOS THREADS DEL SERVIDOR
	static void *IniciarConexiones(void* servidor);


public:
	Servidor();

	void asignarSocketEscucha(int fd);
	int obtenerSocketEscucha();

	void setPuerto(int puerto);
	int getPuerto();

	void setCantidadDeConexiones(int cantidadDeConexiones);
	int getCantidadDeConexiones();

	void setBaseDeDatos(BaseDeDatos* baseDeDatos);
	BaseDeDatos* getBaseDeDatos();

	void mostrarUsuariosDisponibles();

	string getIP();

	int obtenerSocketFD();
	void asignarSocketFD(int fd2);

	void iniciarServidor();
	Socket* aceptarConexiones();



	void finalizarConexiones();
	void cerrarSockets();
	string parsearMensaje(std::string mensaje);
	std::string recibirMensaje(Socket* socket);
	void enviarMensaje(string  mensa, Socket* socket);

	Socket* obtenerSocket();

	void mostrarUsuariosConectados();
	BaseDeDatos* obtenerBaseDeDatos();

	void abrirConexiones();


	~Servidor();


    string validarCliente(string basic_string, string basicString);


    bool getTerminado();

	string procesarMensaje(string unMensaje);
	string agregarPadding(int lenght);
};


#endif /* SERVIDOR_H_ */
