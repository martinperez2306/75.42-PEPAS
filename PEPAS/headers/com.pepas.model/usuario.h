//
// Created by florencia on 06/09/17.
//

#ifndef INC_75_42_PEPAS_USUARIO_H
#define INC_75_42_PEPAS_USUARIO_H

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

    ~Cliente();

};

#endif //INC_75_42_PEPAS_USUARIO_H
