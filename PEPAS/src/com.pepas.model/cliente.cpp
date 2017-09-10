#include "../../headers/com.pepas.model/cliente.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

Cliente::Cliente() {

}

void Cliente::logIn(){
    string usuario;
    string clave;
    cout<<"Ingrese su nombre de usuario"<<endl;
    cin>> usuario;
    cout<<"Ingrese su clave"<<endl;
    cin>> clave;
    this->usuario->setearNombre(usuario);
    this->usuario->setearContrasenia(clave);
}

void Cliente::conectarseAlServidor(string ip, int puerto) {

    struct sockaddr_in server_addr;
    socklen_t server_sock_size;
    socketCliente = socket(AF_INET, SOCK_STREAM, 0);

    /*if (socket_number < 0) {
        LOGGER_WRITE(Logger::ERROR, "Error abriendo el socket.", CLASSNAME)
        cout << "Error abriendo el socket del cliente: " << strerror(errno)
             << endl;
        return false;
    } parte de logger VERRRR!*/

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(puerto);
    server_addr.sin_addr.s_addr = inet_addr(ip.data());
    server_sock_size = sizeof(server_addr);


    /* Me conecto al servidor. Devuelve -1 si la conexion falla */
    /*if (connect(socketCliente, (struct sockaddr *) &server_addr,
                server_sock_size) < 0) {
        LOGGER_WRITE(Logger::ERROR, "Error abriendo el socket.", CLASSNAME)
        cout << "Error conectando al servidor: " << strerror(errno) << endl;
        return false;
    } parte de logger VERRR*/

}


void Cliente::enviarMensaje(string mensaje){
    send (socketCliente, (char *)&mensaje, sizeof (mensaje), 0);
    unsigned Rta;
    recv (socketCliente, (char *)&Rta, sizeof (Rta), 0);
    printf ("Dato enviado: %u, Respuesta recibida: %u\n", mensaje, Rta);
}

void Cliente::desconectarseDelServidor() {
    //neesito ver lo del servidor?
}


Cliente::~Cliente() {

}
