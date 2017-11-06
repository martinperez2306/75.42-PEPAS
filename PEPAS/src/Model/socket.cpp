#include "../../headers/Model/socket.h"
#include "../../headers/Model/logger.h"
#include <unistd.h>
#define MAX_DATA_SIZE 9999

using namespace std;
Socket::Socket(){
    this->fd=0;
    this->puerto=0;
}

int Socket::Crear(){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        cout << "\nError en la creacion del socket" << endl;
        string error = strerror(errno);
        loggear(error,1);
        exit(1);
    }
    return fd;
}

bool Socket::Enlazar(int puerto) {
    this->puerto = puerto;
    struct sockaddr_in serverAddress;
    memset((char *)&serverAddress,0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(puerto);
    socklen_t serverSize = sizeof(serverAddress);

    /*VERIFICACION DE ERRORES*/
    if (bind(fd, (struct sockaddr *) &serverAddress, serverSize) < 0) {
        string error = strerror(errno);
        loggear(error,1);
       // cout << "Error al hacer el enlazado " << error << endl;
        return false;
    }
    return true;
}


//Esta funcion no se usa en el servidor
void Socket::Conectar( int puerto, string IPremota) {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(IPremota.data());
    serverAddress.sin_port = htons(puerto);
    socklen_t serverSize = sizeof(serverAddress);

    /*VERIFICACION DE ERRORES*/
    if (connect(fd, (struct sockaddr *) &serverAddress, serverSize) < 0) {
        string error = strerror(errno);
        loggear(error,1);
        //cout << "Error al conectar con el servidor " << strerror(errno) << endl;
    }

}

void Socket::Escuchar(int socket, int maximasConexionesAlaVez) {
    int ret = listen(socket, maximasConexionesAlaVez);
    /*VERIFICACION DE ERRORES*/
    if (ret  < 0){
        string error = strerror(errno);
       // cout << "Error al escuchar conexiones " << error << endl;
        loggear(error,1);
    }

}

void Socket::Escuchar(int maximasConexionesAlaVez) {
    int ret = listen(fd, maximasConexionesAlaVez);
    /*VERIFICACION DE ERRORES*/
    if (ret  < 0){
        string error = strerror(errno);
       // cout << "Error al escuchar conexiones " << error << endl;
        loggear(error,1);
    }

}

int Socket::AceptarConexion() {
    int socketFD;
    struct sockaddr_in clientAddress;
    socklen_t clientSize =sizeof(clientAddress);
    socketFD = accept(fd, (struct sockaddr *) &clientAddress, &clientSize);
    if (socketFD < 0) {
        string error = strerror(errno);
        loggear(error,1);

        //cout << "Error al conectar con el cliente " << error << endl;

        exit(1);
    }
    return socketFD;
}

std::string chartoString (char* buffer){
    string string = "";
    for (int i = 0; i< strlen(buffer);i++){
        string = string + buffer[i];
    }
    return string;
}

void Socket::Enviar(const void *mensaje, size_t mensajeLength) {
    ssize_t totalEnviado= 0;
    ssize_t ultimaCantidadEnviada = 0;
    while (totalEnviado < mensajeLength){
        ultimaCantidadEnviada = send(fd, mensaje + totalEnviado, mensajeLength-totalEnviado, MSG_NOSIGNAL);
        if (ultimaCantidadEnviada < 0) {
            string error = strerror(errno);
            loggear("Error al enviar mensaje: " + error,1);
           // cout << "Error al enviar mensaje " << error << endl;
            break;

        } else {
            totalEnviado += ultimaCantidadEnviada;

        }
    }

}


std::string Socket::Recibir( size_t mensajeAleerLength) {
    bool socketShutDown = false;
    ssize_t totalRecibido = 0;
    string cadenaAdevolver ;//= "";
    char buffer[MAX_DATA_SIZE] = {0};
    ssize_t ultimaCantidadRecibida = 0;
    while (totalRecibido < mensajeAleerLength && !socketShutDown) { //
        ultimaCantidadRecibida = recv(fd, buffer, mensajeAleerLength - totalRecibido, 0);
        if (ultimaCantidadRecibida < 0) {
            socketShutDown = true;
            string error = strerror(errno);
            cadenaAdevolver = "0006/"+to_string(fd);
            //cout << "Error al recibir mensaje " << error << endl;
            loggear("Error al recibir mensaje: " + error,1);
        } else if (ultimaCantidadRecibida == 0) {
            socketShutDown = true;
            cadenaAdevolver = "0006/"+to_string(fd);
            loggear("Recibi un 0, cadenaAdevolver = 6",1);
           // CerrarConexion();
        } else {
            totalRecibido += ultimaCantidadRecibida;

        }
    }
    if (ultimaCantidadRecibida < 0) {
        string error = strerror(errno);
        loggear(error,1);
       // cout << "Error al recibir el mensaje " << error << endl;
    }

    if (ultimaCantidadRecibida > 0) {
        cadenaAdevolver = chartoString(buffer);

    }
    cout<<cadenaAdevolver<<endl;
    return cadenaAdevolver;

}


void Socket::CerrarConexion() {
    int ret = shutdown(fd, SHUT_WR);

    /*VERIFICACION DE ERRORES*/
    if (ret < 0){
        string error = strerror(errno);
        loggear("Error al cerrar conexion: " + error,1);
       // cout << "Error al cerrar conexion " << error << endl;
    }
}
void Socket::CerrarConexion(int socket) {
    int ret = shutdown(socket, SHUT_RDWR);

    /*VERIFICACION DE ERRORES*/
    if (ret < 0){
        string error = strerror(errno);
loggear("Error al cerrar conexion " + error,1);
    }
}
void Socket::CerrarSocket(int socket) {
    int ret = close(socket);
    if (ret == -1){
        string error = strerror(errno);
        cout<<"Error en el cierre del socket" <<error<<endl;
    }
}



Socket::~Socket(){
}

int Socket::obtenerFD() {
    return this->fd;
}

void Socket::asignarFD(int newFD) {
    this->fd = newFD;

}

int Socket::obtenerPuerto() {
    return this->puerto;
}

