/*
 * clienteController2.h
 *
 *  Created on: 6 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_
#define COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_


//
// Created by florencia on 03/09/17.
//

#include "../com.pepas.model/cliente.h"
#include "../com.pepas.parser/ClienteParser.h"


class ClienteController{


private:
    Cliente* cliente;
    ClienteParser* clienteParser;

public:
    ClienteController();

    ClienteController(ClienteParser *ClienteParser);

    void crearCliente();

    void conectarConElServidor();

    void desconectarseDelServidor();

    void mensajeDePrueba();

    void logIn(char* nombre, char* contrasenia);

    void logOut();

    void stressTest();

    void enviarMensajeChat();

    void enviarMensajePrivado();

    void asignarServidor();

    void salirDelPrograma();

    ~ClienteController();

};

#endif /* COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_ */
