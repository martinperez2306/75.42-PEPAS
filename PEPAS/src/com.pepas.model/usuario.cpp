//
// Created by florencia on 06/09/17.
//

#include "../../headers/com.pepas.model/usuario.h"

Usuario::Usuario(){
    this->nombre = "";
    this->contrasenia = "";
}

void Usuario::setearNombre(string nombre) {
    this->nombre = nombre;
}

void Usuario::setearContrasenia(string contrasenia) {
    this->contrasenia = contrasenia;
}

string Usuario::getNombre(){
    return this->nombre;
}

string Usuario::getContrasenia(){
    return this->contrasenia;
}
