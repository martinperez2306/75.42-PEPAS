/*
 * cliente.h
 *
 *  Created on: 6 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_MODEL_CLIENTE_H_
#define COM_PEPAS_MODEL_CLIENTE_H_


#include <string>
#include "usuario.h"
#include "socket.h"
#include "Mensaje.h"
#include "minimapa.h"
#include "Mapa.h"
#include "../com.pepas.view/vista.h"
#include "Rival.h"
#include <iostream>
#include <cstring>
#include <list>


using namespace std;


struct scores {
    string scoreEtapa;
    string scoreTotal;
    string pistaActual;
};

class Cliente{

private:
    Usuario* usuario;
    Socket* socketCliente;
    int socketFD, posY, posX,velocidad;
    int aliveCounter, modelCar, cantidadJugadores, cantidadADibujar;
    bool logueado;
    bool conectado;
    bool minimapaCompleto;
    bool mapaCompleto;
    bool finDeMapa;
    list<string> colaBuzon;
    list<string> colaChat;
    list<pair<int, float>>Track;

    Minimapa* minimapa;
    Mapa* mapa;
    Vista* vista;
    string tiempo;
    bool mover, pressEnter, grisado;
    int destrozo;
    list<pair<string,scores>>* scoresUsuarios;


public:

    list<Rival*> rivalList;
    Cliente();
    bool minimapaEstaCompleto();
    bool mapaEstaCompleto();
    void logIn(string usuario, string clave);

    //metodo para loquearse?
    int conectarseAlServidor(const char *ip, int puerto);

    void enviarMensaje(string mensaje);

    void desconectarseDelServidor();

    void asignarSocketFd(int crear);

    int obtenerSocketFD();

    Socket* obtenerSocket();

    Usuario *obtenerUsuario();

    ~Cliente();

    void validarUsuario(Usuario* usuario);

    string procesarMensaje(string usuario, string contrasenia);

    string procesarMensaje(Mensaje* mensaje);
    string procesarMensaje(string usuario);

    string obtenerCodigo();

    string agregarPadding(int i);

    void parsearMensaje(std::string datos);

    std::string recibirMensaje();

    bool estalogueado();

    string armarMensaje(string emisor, string mensa);

    list<string> obtenerColaChat();

    list<string> obtenerColaBuzon();
    list<pair<int, float>> obtenerTrack();
    Mapa* obtenerMapa();
    void desloguearse();
    void desencolarColaChat();
    void desencolarColaBuzon();
    void verBuzon();
    bool estaConectado();
    bool estaConectadoYLogueado();
    void conectarse();
    void desconectarse();
    void vaciarColaChat();
    void vaciarColaBuzon();
    int obtenerAliveCounter();
    void graficarMinimapa();
    void actualizarRutaMiniMapa(int x1, int y1, int x2,int y2);
    void actualizarObjetosMiniMapa(int arbol, int cartel, int distancia, string lado);
    void actualizarRutaMapa(int longitud, int curva);
    void actualizarObjetosMapa(int arbol, int cartel, int distancia, string lado);

    void setPosY(int i);

    void setPosX(int i);

    int getPosition();

    int getX();
    int obtenerCantidadJugadores();
Minimapa* getMinimapa();

    bool recibioFinDeMapa();

    int obtenerModel();

    void parsearCalculos(string datos, int i);

    int cantidadAdibujar();


    void crearRivales(int i, int MiPos);

    int setRival(string basic_string, int i);

    int obtenerCantidadDePlayersADibujar();

    list<Rival*> obtenerRivalList();

    int getY();

void setVelocidad(int vel);

int getVelocidad();
string getTiempo();
bool sePuedeMover();

    int getDestrozo();

    void setRecibioFinDeMapa();

    void noMover();

    list<pair<string,scores>>* getScores();

    void setFinDeMapa(bool finDeMapa);

    bool recibioPressEnter();

    void setPressEnter();

    bool getGrisado();

    void grisarAuto();

    void noGrisarAuto();
};



#endif /* COM_PEPAS_MODEL_CLIENTE_H_ */
