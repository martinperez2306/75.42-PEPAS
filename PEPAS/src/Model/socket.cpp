#include "../../headers/Model/socket.h"
#include "../../headers/Model/logger.h"

#define MAX_DATA_SIZE 9999

using namespace std;
Socket::Socket(){
    this->fd=0;
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

void Socket::Enlazar(int puerto) {
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
        cout << "Error al hacer el enlazado " << error << endl;
        exit(1);
    }
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
        cout << "Error al conectar con el servidor " << strerror(errno) << endl;
    }

}

void Socket::Escuchar(int socket, int maximasConexionesAlaVez) {
    int ret = listen(socket, maximasConexionesAlaVez);
    /*VERIFICACION DE ERRORES*/
    if (ret  < 0){
        string error = strerror(errno);
        cout << "Error al escuchar conexiones " << error << endl;
        loggear(error,1);
    }

}

void Socket::Escuchar(int maximasConexionesAlaVez) {
    int ret = listen(fd, maximasConexionesAlaVez);
    /*VERIFICACION DE ERRORES*/
    if (ret  < 0){
        string error = strerror(errno);
        cout << "Error al escuchar conexiones " << error << endl;
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

        cout << "Error al conectar con el cliente " << error << endl;

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
            //LOGGER INFo
            loggear(error,1);
            cout << "Error al enviar mensaje " << error << endl;

        } else {
            totalEnviado += ultimaCantidadEnviada;

        }
    }
    if(ultimaCantidadEnviada < 0){
        string error = strerror(errno);
        //LOGGER INFo
        cout << "Error al enviar mensaje " << error << endl;

    }
    cout<<ultimaCantidadEnviada<<endl;
}


std::string Socket::Recibir( size_t mensajeAleerLength) {
    bool socketShutDown = false;
    ssize_t totalRecibido = 0;
    char buffer[MAX_DATA_SIZE] = {0};
    ssize_t ultimaCantidadRecibida = 0;
    while (totalRecibido < mensajeAleerLength) { // && !socketShutDown
        ultimaCantidadRecibida = recv(fd, buffer, mensajeAleerLength - totalRecibido, 0);
        if (ultimaCantidadRecibida < 0) {
            string error = strerror(errno);
            cout << "Error al recibir mensaje " << error << endl;
        } else if (ultimaCantidadRecibida == 0) {
            socketShutDown = true;
        } else {
            totalRecibido += ultimaCantidadRecibida;

        }
    }
    if (ultimaCantidadRecibida < 0) {
        string error = strerror(errno);
        loggear(error,1);
        cout << "Error al recibir el mensaje " << error << endl;
    }

    cout << "Antes de convertir a string: "<<buffer << endl;
    string  cadenaAdevolver = chartoString (buffer);

    cout<< "El mensaje recibido fue: "<<cadenaAdevolver<<endl;
    cout<< "El ultimo recv fue de "<<ultimaCantidadRecibida<< " bytes"<<endl;
    return cadenaAdevolver;

}


void Socket::CerrarConexion() {
    int ret = shutdown(fd, SHUT_WR);

    /*VERIFICACION DE ERRORES*/
    if (ret < 0){
        string error = strerror(errno);
        //LOGGEER INFO
        cout << "Error al cerrar conexion " << error << endl;
    }
}
void Socket::CerrarConexion(int socket) {
    int ret = shutdown(socket, SHUT_RDWR);

    /*VERIFICACION DE ERRORES*/
    if (ret < 0){
        string error = strerror(errno);
        //LOGGEER INFO
        cout << "Error al cerrar conexion " << error << endl;
    }
}

void Socket::CerrarSocket() {
    //close(fd);
}


Socket::~Socket(){
}

int Socket::obtenerFD() {
    return this->fd;
}

void Socket::asignarFD(int newFD) {
    this->fd = newFD;

}

