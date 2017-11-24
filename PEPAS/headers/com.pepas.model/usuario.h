//
// Created by florencia on 06/09/17.
//

#ifndef COM_PEPAS_MODEL_USUARIO_H
#define COM_PEPAS_MODEL_USUARIO_H

#include <string>
#include <iostream>

using namespace std;

class Usuario{

private:
    string nombre;
    string contrasenia;


public:
    Usuario();

    void setearNombre(string nombre);

    void setearContrasenia(string contrasenia);

    string getNombre();

    string getContrasenia();

    ~Usuario();

    void enviarMensajeAlServidor();
};

#endif //COM_PEPAS_MODEL_USUARIO_H
