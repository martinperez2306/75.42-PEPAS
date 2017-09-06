//
// Created by arturi on 04/09/17.
//

#ifndef INC_75_42_PEPAS_SOCKET_H
#define INC_75_42_PEPAS_SOCKET_H
#include <cstring>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
using namespace std;
class Socket {

    private:
        int puerto;

    public:


        Socket();

        int Crear();

        void Enlazar (int socket, int puerto, string serverIP);

        void Conectar(int socket, int puerto, string IP);

        void Escuchar(int socket, int maximasConexiones);

        void AceptarConexion(int socket);

        void Enviar(int socket, const void *mensaje, size_t mensajeLength);

        void Recibir(int socket, char mensajeArecibir[], size_t mensajeAleerLength);

        void CerrarConexion(int socket);


        ~Socket();

    };


#endif //INC_75_42_PEPAS_SOCKET_H
