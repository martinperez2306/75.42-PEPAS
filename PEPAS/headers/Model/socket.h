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
        int fd;

    public:

/*    Los pasos para establecer un socket del lado del servidor son:
    1. Crear un socket con la función socket()
    2. Enlazar el socket a una dirección utilizando la función bind(). Para un socket en internet, la
            dirección consiste en un numero de puerto en la maquina donde es ejecutado.
    3. Escuchar por conexiones con la función listen()
    4. Aceptar conexiones con la función accept()
    5. Enviar y recibir datos con send() y recv()
    6. Finalizar la transmisión en el socket que escucha conexiones con shutdown()
    7. Cerrar todos los sockets debidamente con close() al finalizar.*/

        Socket();


    /*  Crea el socket obteniendo un filedescriptor del sistema operativo. Recibe las características de configuración básicas.*/
        int Crear();

        /* Enlaza el socket identificado por el filedescriptor con una dirección y puerto locales.*/
        void Enlazar (int puerto);

      /*  Conecta el socket a la dirección y puerto destino.
        Determina dirección y puertos locales si no se utilizó bind() previamente.*/

        void Conectar(int puerto, string IP);

        /*Configura el socket para recibir conexiones en la dirección y
        puerto previamente determinada mediante bind().*/
        void Escuchar(int socket, int maximasConexiones);
        void Escuchar(int maximasConexiones);

        int AceptarConexion();

       /* Envía datos a través del socket*/
        void Enviar(const void *mensaje, size_t mensajeLength);


        /*Recibe datos a través del socket*/
        std::string Recibir(size_t mensajeAleerLength);

        /*Se utiliza para cerrar el envío y la recepción de datos en
        forma ordenada*/
        void CerrarConexion();
        void CerrarConexion(int socket);

        /*Se utiliza para cerrar el socket y liberar los recursos.*/
        void CerrarSocket();

        int obtenerFD();

        ~Socket();

    void asignarFD(int i);
};


#endif //INC_75_42_PEPAS_SOCKET_H
