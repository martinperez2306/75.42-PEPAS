//
// Created by florencia on 03/09/17.
//

#ifndef INC_75_42_PEPAS_CLIENTE_CLIENTECONTROLLER_H
#define INC_75_42_PEPAS_CLIENTE_CLIENTECONTROLLER_H

#include "../com.pepas.model/cliente.h"
//#include"servidorBuilder.h


class ClienteController{


private:
    Cliente* cliente;
   // ServidorBuilder* servidorBuilder;

public:
    ClienteController();

    void crearCliente();

    //int getPuertoServidor();

    //int getMaximoClientesServidor();

    //Usuario* getUsuario();

    void conectarConElServidor();

    void desconectarseDelServidor();

    void logIn();

    void stressTest();

    void enviarMensajeChat();

    void enviarMensajePrivado(){

    }

    ~ClienteController();

};

#endif //INC_75_42_PEPAS_CLIENTE_CLIENTECONTROLLER_H
