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
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/recvThread.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/aliveSignalThread.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/threadMinimapa.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/cliente.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/Mensaje.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.parser/ClienteParser.h"


class ClienteController{



private:

    ClienteParser* clienteParser;
    ClienteParser::SocketData socketData;
    Cliente* cliente;
    recvThread threadRecibir;
    aliveSignalThread threadEnviar;
    threadMinimapa threadGraficoMinimapa;
    bool reconexion;
    char ipAddress[20];
    char testFile [100];


public:

    ClienteController(const char* archivo);

    ClienteController(ClienteParser *ClienteParser);

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
    void logIn();
    void entrarAlChat();
    void verBuzon();

    void enviarBroadcast(string entradita);
    void conectar();
    void verMinimapa();

};

#endif /* COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_ */
