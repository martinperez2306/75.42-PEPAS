//
// Created by florencia on 03/09/17.
//

#ifndef INC_75_42_PEPAS_CLIENTE_CONSOLA_H
#define INC_75_42_PEPAS_CLIENTE_CONSOLA_H

#include <iostream>
#include <string>
#include "clienteController.h"
#include <stdlib.h>


using namespace std;

class Consola{

private:
    bool terminado;
    //int numeroPagina;
    ClienteController* clienteController;
public:

    Consola();

    void setTerminado(bool terminado);
    bool getTerminado();

    /////////////////Cargar Paginas/////////////////
    void cargarPagina(int numeroPagina);
    void cargarPaginaPrincipal();
    void cargarIngresarUsuario();
    void cargarPaginaCaracteristicasDelCliente();
    void cargarPaginaCrearCliente();

    ~Consola();
};

#endif //INC_75_42_PEPAS_CLIENTE_CONSOLA_H
