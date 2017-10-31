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
#include "../com.pepas.view/vista.h"
#include <iostream>
#include <cstring>
#include <list>


using namespace std;

class Cliente{

private:
    Usuario* usuario;
    Socket* socketCliente;
    int socketFD;
    int aliveCounter;
    bool logueado;
    bool conectado;
    bool minimapaCompleto;
    list<string> colaBuzon;
    list<string> colaChat;
    list<pair<int, float>>Track;
    Minimapa* minimapa;
    Vista* vista;


public:
    Cliente();
    bool minimapaEstaCompleto();
    void logIn();

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

};



#endif /* COM_PEPAS_MODEL_CLIENTE_H_ */
