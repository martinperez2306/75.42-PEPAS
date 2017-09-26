/*
 * cliente.h
 *
 *  Created on: 6 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_MODEL_CLIENTE_H_
#define COM_PEPAS_MODEL_CLIENTE_H_


#include <string>
#include "../../headers/com.pepas.model/usuario.h"
#include "../../headers/com.pepas.model/socket.h"
#include "../../headers/com.pepas.model/Mensaje.h"
#include <iostream>
#include <cstring>
#include <list>

using namespace std;

class Cliente{

private:
    Usuario* usuario;
    Socket* socketCliente;
    int socketFD;
    bool logueado;
    list<string> colaBuzon;
    list<string> colaChat;


public:
    Cliente();

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
    void desloguearse();
    void desencolarColaChat();
};



#endif /* COM_PEPAS_MODEL_CLIENTE_H_ */
