#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "baseDeDatos.h"
#include "socket.h"
#include <list>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "minimapa.h"
#include "pistaParser.h"
#include "Zoomer.h"


class Servidor{

private:
	int puerto;
	int cantidadMaximaDeConexiones;
	int conexiones;
	int socketFD;
	int socketEscucha;

	bool terminado;
	BaseDeDatos* baseDeDatos;
	Socket* iniciarConexion(int puerto);
	Socket* serverSocket;
	std::list<int> puertosDisponibles;
	std::list<int> puertosEnUso;
	unordered_map<int, int> mapFD; // <socketFD, puerto>
	map<int,Socket*>* mapaSocket; // <puerto, Socket>
	map<int, string>* mapUsuario;

	PistaParser* pistaParser;
	Mapa* mapa;
	Minimapa* minimapa;
	Zoomer* zoomer;

public:
	int aliveCounter;
	Servidor();

	void asignarSocketEscucha(int fd);
	int obtenerSocketEscucha();

	void setPuerto(int puerto);
	int getPuerto();

	void setCantidadMaximaDeConexiones(int cantidadMaximaDeConexiones);
	int getCantidadMaximaDeConexiones();
	void mostrarTodosLosUsuariosConectados();

	void setBaseDeDatos(BaseDeDatos* baseDeDatos);
	BaseDeDatos* getBaseDeDatos();

	void mostrarUsuariosDisponibles();


	int obtenerSocketFD();
	void asignarSocketFD(int fd2);

	void iniciarServidor();
	Socket* aceptarConexiones();



	void finalizarConexiones();
	void cerrarSockets();
	string parsearMensaje(std::string mensaje, Socket* socket);
	std::string recibirMensaje(Socket* socket);
	void enviarMensaje(string  mensa, Socket* socket);

	Socket* obtenerSocket();

	void mostrarUsuariosConectados();
	BaseDeDatos* obtenerBaseDeDatos();


	~Servidor();


    string validarCliente(string basic_string, string basicString, Socket* emisor);


    bool getTerminado();

	string procesarMensaje(string unMensaje);
	string agregarPadding(int lenght);
	void desloguearse(string usuario,Socket* socketDelemisor);

	int obtenerAlive ();

	void setZoomEntreMapaYMinimapa(int zoom);
	string procesarMensajeRutaMinimapa(int x1, int y1, int x2, int y2);
	string procesarMensajeObjetoMinimapa(int arbol,int cartel,int distancia,string lado);
	void generarMapa();
	void generarMinimapa();
	void enviarMinimapaACliente(Socket* socketCliente);
	string procesarMensajeFinMinimapa();
};


#endif /* SERVIDOR_H_ */
