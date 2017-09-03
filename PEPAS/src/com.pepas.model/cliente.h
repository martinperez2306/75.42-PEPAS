//
// Created by florencia on 03/09/17.
//

#ifndef INC_75_42_PEPAS_CLIENTE_CLIENTE_H
#define INC_75_42_PEPAS_CLIENTE_CLIENTE_H

#include <string>
using namespace std;

class Cliente{


private:
    string usuario;
    string contrasenia;
    string IPservidor;
    int puertoServidor;


public:

    Cliente();

    Cliente(string usuario, string contrasenia);

    void setUsuario(string usuario);

    void setContrasenia(string contrasenia);

    string getUsuario();

    string getContrasenia();
};

#endif //INC_75_42_PEPAS_CLIENTE_CLIENTE_H
