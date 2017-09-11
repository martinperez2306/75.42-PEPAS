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
#include "../com.pepas.model/Mensaje.h"
#include "../com.pepas.parser/ClienteParser.h"


class ClienteController{



private:

    ClienteParser* clienteParser;
    ClienteParser::SocketData socketData;

public:
    Cliente* cliente;
    ClienteController();

    ClienteController(ClienteParser *ClienteParser);

    void crearCliente();

    void conectarConElServidor();

    void asignarServidor();

    void desconectarseDelServidor();

    void mensajeDePrueba();

    void logOut();

    void stressTest();

    void enviarMensajeChat();

    void enviarMensajePrivado();


    void salirDelPrograma();

    ~ClienteController();

    Cliente *obtenerCliente();
};

#endif /* COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_ */
