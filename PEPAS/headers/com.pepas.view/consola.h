#ifndef COM_PEPAS_CONSOLA_CONSOLA_H
#define COM_PEPAS_CONSOLA_CONSOLA_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>
#include "../com.pepas.controllers/clienteController.h"
#include <stdlib.h>
#define BUFLEN 1000

using namespace std;

class Consola{

private:
    //int numeroPagina;
    ClienteController* clienteController;
    bool terminado;
public:

    Consola();

    /////////////////Cargar Paginas/////////////////
    void *cargarPagina();
    void cargarPaginaPrincipal();
    void cargarIngresarUsuario();
    void cargarPaginaCaracteristicasDelCliente();
    void cargarPaginaCrearCliente();
    void cargarLogIn();
    void cargarMenuPrincipal();
    bool terminoConsola();
    ClienteController* getController();

    ~Consola();
};

#endif //COM_PEPAS_CONSOLA_CONSOLA_H
