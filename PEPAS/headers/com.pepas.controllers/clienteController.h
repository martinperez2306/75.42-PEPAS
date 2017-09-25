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
#include "../com.pepas.model/recvThread.h"
#include "../com.pepas.model/cliente.h"
#include "../com.pepas.model/Mensaje.h"
#include "../com.pepas.parser/ClienteParser.h"


class ClienteController{



private:

    ClienteParser* clienteParser;
    ClienteParser::SocketData socketData;
    recvThread threadRecibir = recvThread(cliente);
    Cliente* cliente;

    

public:
    
    ClienteController();

    ClienteController(ClienteParser *ClienteParser);

    void crearCliente();

    int conectarConElServidor();

    void desconectarseDelServidor();

    void logOut();

    void stressTest();


    void enviarMensajePrivado();
    void empezarRecibir();
    void dejarRecibir();


    void salirDelPrograma();

    ~ClienteController();

    Cliente *obtenerCliente();

    void obtengoPuertoNuevoYHagoConectar();;

    void entrarAlChat();
    void verBuzon();
};

#endif /* COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_ */
