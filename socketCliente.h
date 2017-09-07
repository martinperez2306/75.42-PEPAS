#ifndef INC_75_42_PEPAS_SOCKET_H
#define INC_75_42_PEPAS_SOCKET_H

#include <cstring>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>

using namespace std;


class SocketCliente{

private:

    int puerto;

public:

    SocketCliente();

    int crear();

    void Enlazar(int socket, int puerto, string serverIP);

    void Conectar(int socket, int puerto, string IP);

    void Escuchar(int socket, int maximasConexiones);

    void AceptarConexion(int socket);

    void Enviar(int socket, const void *mensaje, size_t mensajeLength);

    //void socketRecibir(socket_t *socket_fd, char messageToRecieve[], size_t messageToReadLength, int *readMsgLength);

    //void CerrarConexion(socket_t *socket_fd);

    ~SocketCliente();

};

#endif //INC_75_42_PEPAS_SOCKET_H
