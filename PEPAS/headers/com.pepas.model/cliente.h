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

using namespace std;

class Cliente{

private:
    Usuario* usuario;
    Socket* socketCliente;
    int socketFD;

public:
    Cliente();

    void logIn();

    //metodo para loquearse?
    void conectarseAlServidor(string ip, int puerto);

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

    string obtenerCodigo();

    string agregarPadding(int i);
};



#endif /* COM_PEPAS_MODEL_CLIENTE_H_ */
