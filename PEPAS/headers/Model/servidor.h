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
#include "World.h"
#include "Zoomer.h"
#include "Logica.h"
#include "Auto.h"
#include "Recorredor.h"
#include "TimerThread.h"
#include <ctime>



class Servidor{

private:
	int puerto;
	int cantidadMaximaDeConexiones;
	int conexiones;
	int socketFD;
	int socketEscucha;
	int player;
	bool terminado;
    bool empezarJuego;
	bool colision;
	BaseDeDatos* baseDeDatos;
	Socket* iniciarConexion(int puerto);
	Socket* serverSocket;
	std::list<int> puertosDisponibles;
	std::list<int> puertosEnUso;
    std::list<int> modeloDeAuto;
	std::list<string> grisados;
	unordered_map<int, int> mapFD; // <socketFD, puerto>
	map<int,Socket*>* mapaSocket; // <puerto, Socket>
	map<int, string>* mapUsuario;
    map<int,Mapa*>* mapas;
	PistaParser* pistaParser;
	Mapa* mapa;
	Minimapa* minimapa;
	World* world;
	Zoomer* zoomer;
    Recorredor* recorredor;
    string time;
	Logica* logicaJuego;
	map<string, Auto*>* mapAutitos;
    TimerThread timerThread = TimerThread (false);
    bool carreraTerminada;
    int pistaActual;
    int jugadoresListos;
    bool listos;

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
	string procesarMensajeRutaMapa(int longitud, int curva);
	string procesarMensajeObjetoMapa(int arbol,int cartel,int distancia,string lado);
	string procesarMensajeFin();
	string procesarMensajeCambioDePista();

	void generarMapa();
	void generarMinimapa();
	void enviarMapaACliente(Socket* socketCliente);
	void enviarMinimapaACliente(Socket* socketCliente);
	void enviarFinMapas(Socket* socketCliente);
	void generarWorld();

    list<int> cargarLista();

    bool getEmpezoJuego();

	bool hayColision();

    void setEmpezoJuego(bool i);

	string obtenerUsuarioConFd(int fd);

	Auto* obtenerAutoConId(string id);

	int curvaEnKilometraje(int posicionY);

	string actualizarJuego(Auto *pAuto);

	list<string> obtenerGrisados();

    void setMapa(int i);

    clock_t obtenerTime();

    string renderTiempo(clock_t sTime);

    void setTime(string basic_string);

    string getTime ();
	bool estaListo();
};


#endif /* SERVIDOR_H_ */
