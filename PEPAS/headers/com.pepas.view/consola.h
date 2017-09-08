//
// Created by florencia on 03/09/17.
//

#ifndef COM_PEPAS_CONSOLA_CONSOLA_H
#define COM_PEPAS_CONSOLA_CONSOLA_H

#include <iostream>
#include <string>
#include "../com.pepas.controllers/clienteController.h"
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
    void cargarPagina();
    void cargarPaginaPrincipal();
    void cargarIngresarUsuario();
    void cargarPaginaCaracteristicasDelCliente();
    void cargarPaginaCrearCliente();
    void cargarLogIn();
    void cargarMenuPrincipal();

    ~Consola();
};

#endif //COM_PEPAS_CONSOLA_CONSOLA_H
