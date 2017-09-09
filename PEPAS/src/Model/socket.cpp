//
// Created by arturi on 04/09/17.
//



#include "../../headers/Model/socket.h"


using namespace std;
Socket::Socket(){

    int puerto = 0;


}

int Socket::Crear(){
int sockett;
    sockett = socket(AF_INET, SOCK_STREAM, 0);
    if (sockett < 0) {
        cout << "\nError en la creacion del socket" << endl;
    //AGREGAR ERROR AL LOGGER
        exit(1);
    }
    return sockett;
}

void Socket::Enlazar(int socket, int puerto, string serverIP) {
    int bindsocket = socket;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIP.data());
    serverAddress.sin_port = htons(puerto);
    socklen_t serverSize = sizeof(serverAddress);

    /*VERIFICACION DE ERRORES*/
    if (bind(bindsocket, (struct sockaddr *) &serverAddress, serverSize) < 0) {
        string error = strerror(errno);
        //AGREGAR ERROR AL LOGGER
        cout << "Error al hacer el enlazado " << error << endl;
        //exit(1);
    }
}

void Socket::Conectar(int socket, int puerto, string IPremota) {
    int connectSocket = socket;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(IPremota.data());
    serverAddress.sin_port = htons(puerto);
    socklen_t serverSize = sizeof(serverAddress);

    /*VERIFICACION DE ERRORES*/
    if (connect(connectSocket, (struct sockaddr *) &serverAddress, serverSize) < 0) {
        // logger info
        cout << "Error al conectar con el servidor " << strerror(errno) << endl;
    }

}

void Socket::Escuchar(int socket, int maximasConexiones) {
    int ret = listen(socket, maximasConexiones);

    /*VERIFICACION DE ERRORES*/
    if (ret  < 0){
        string error = strerror(errno);
        cout << "Error al escuchar conexiones " << error << endl;
    }

}

void Socket::AceptarConexion(int listenSocket) {
    int clientID;
    struct sockaddr_in clientAddress;
    socklen_t clientSize;
    clientID = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientSize);

    if (clientID < 0) {
        string error = strerror(errno);
        //LOGGER INFO

        cout << "Error al conectar con el cliente " << error << endl;

        //exit(1);
    }
}

void Socket::Enviar(int socket, const void *mensaje, size_t mensajeLength) {
        ssize_t totalSentAmount = 0;
        ssize_t mensajeEnviado = send(socket, mensaje, mensajeLength, MSG_NOSIGNAL);
            if (mensajeEnviado < 0) {
                string error = strerror(errno);
                //LOGGER INFo
                cout << "Error al enviar mensaje " << error << endl;

        }

}

void Socket::Recibir(int socket, char *mensajeArecibir, size_t mensajeAleerLength) {
        bool socketShutDown = false;
        ssize_t ultimoMensajeRecibido = 0;
        ultimoMensajeRecibido = recv(socket, &mensajeArecibir, mensajeAleerLength, MSG_NOSIGNAL);
        if (ultimoMensajeRecibido < 0){
            string error = strerror(errno);
            //LOGGEER INFO
            cout << "Error al recibir el mensaje " << error << endl;
    }
}

void Socket::CerrarConexion(int socket) {
    int ret = shutdown(socket, SHUT_WR);

    /*VERIFICACION DE ERRORES*/
    if (ret < 0){
        string error = strerror(errno);
        //LOGGEER INFO
        cout << "Error al recibir el mensaje " << error << endl;
    }
}


