#include "cliente.h"

Cliente::Cliente(){
    this->contrasenia = "";
    this->usuario = "";
    this->IPservidor;
    this-> puertoServidor;
}

Cliente::Cliente(string usuario,string contrasenia){

    this->usuario = usuario;
    this->contrasenia = contrasenia;

}

void Cliente::setUsuario(string usuario){

    this->usuario = usuario;
}

void Cliente::setContrasenia(string contrasenia){

    this->contrasenia = contrasenia;
}

string Cliente::getContrasenia(){
    return this->contrasenia;
}

string Cliente::getUsuario(){
    return this->usuario;
}





