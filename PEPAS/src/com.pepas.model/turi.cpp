#ifndef INC_75_42_PEPAS_SOCKET_H
#define INC_75_42_PEPAS_SOCKET_H
#include <cstring>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
using namespace std;
  int Crear();

        void Enlazar (int socket, int puerto, string serverIP);

        void Conectar(int socket, int puerto, string IP);

        void Escuchar(int socket, int maximasConexiones);

        void AceptarConexion(int socket);

        void Enviar(int socket, const void *mensaje, size_t mensajeLength);

        void socketRecibir(socket_t *socket_fd, char messageToRecieve[], size_t messageToReadLength, int *readMsgLength);

        void CerrarConexion(socket_t *socket_fd);

  
  
  *******************************************************************************************************
    
#include "../../headers/Model/socket.h"


using namespace std;
Socket::Socket(){

    int puerto = NULL;


}

int Socket::Crear(){
int socket;
    socket = socket(AF_INET, SOCK_STREAM, 0);
    if (socket     < 0) {
        cout << "\nError en la creacion del socket" << endl;
    //AGREGAR ERROR AL LOGGER
        exit(1);
    }
    return socket;

}

// void Socket::Enlazar(int socket, int puerto, string serverIP) {
//     int bindsocket = socket;
//     struct sockaddr_in serverAddress;
//     serverAddress.sin_family = AF_INET;
//     serverAddress.sin_addr.s_addr = inet_addr(serverIP.data());
//     serverAddress.sin_port = htons(puerto);
//     socklen_t serverSize = sizeof(serverAddress);

//     /*VERIFICACION DE ERRORES*/
//     if (bind(bindsocket, (struct sockaddr *) &serverAddress, serverSize) < 0) {
//         string error = strerror(errno);
//         //AGREGAR ERROR AL LOGGER
//         cout << "Error al hacer el enlazado" << error << endl;
//         //exit(1);
//     }
// }

void Socket::Conectar(int socket, int puerto, string IP) {
    int connectSocket = socket;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(IP.data());
    serverAddress.sin_port = htons(puerto);
    socklen_t serverSize = sizeof(serverAddress);

    /*VERIFICACION DE ERRORES*/
    if (connect(connectSocket, (struct sockaddr *) &serverAddress, serverSize) < 0) {
        // logger info
        cout << "Error al conectar con el servidor " << strerror(errno) << endl;
    }

}

// void Socket::Escuchar(int socket, int maximasConexiones) {
//     // int ret = listen(socket, maximasConexiones);

//     // /*VERIFICACION DE ERRORES*/
//     // if (ret  < 0){
//     //     string error = strerror(errno);
//     //     cout << "Error al escuchar conexiones " << error << endl;
//     // }

// }

// void Socket::AceptarConexion(int listenSocket) {
// //     int clientID;
// //     struct sockaddr_in clientAddress;
// //     socklen_t clientSize;
// //     clientID = accept(listenSocket, (struct sockaddr *) &clientAddress, &clientSize);

// //     if (clientID < 0) {
// //         string error = strerror(errno);
// //         //LOGGER INFO

// //         cout << "Error al conectar con el cliente" << error << endl;

// //         //exit(1);
// //     }
// // }
  
  
void Socket::Enviar(int socket, const void *mensaje, size_t mensajeLength) {
        ssize_t totalSentAmount = 0;
        ssize_t mensajeEnviado = send(socket, mensaje, mensajeLength, MSG_NOSIGNAL);
            if (mensajeEnviado < 0) {
                string error = strerror(errno);
                //LOGGER INFo
                cout << "Error al enviar mensaje " << error << endl;

        }

}
  

