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
using namespace std;

class Cliente{

private:
    Usuario* usuario = new Usuario();
    int socketCliente;

public:
    Cliente();

    void logIn();

    //metodo para loquearse?
    void conectarseAlServidor(string ip, int puerto);

    void enviarMensajePrueba();

    void desconectarseDelServidor();
    ~Cliente();

};



#endif /* COM_PEPAS_MODEL_CLIENTE_H_ */
