#include "../../headers/com.pepas.model/socket.h"
#include "../../headers/com.pepas.logger/Logger.h"

#define MAX_DATA_SIZE 1000

using namespace std;
Socket::Socket(){

    puerto = 0;
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
        char* error = strerror(errno);
        //AGREGAR ERROR AL LOGGER
        cout << "Error al hacer el enlazado " << error << endl;
        //exit(1);
    }
}

int Socket::Conectar(int socket, int puerto, const char *IPremota) {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(IPremota);
    serverAddress.sin_port = htons(puerto);
    socklen_t serverSize = sizeof(serverAddress);
    /*VERIFICACION DE ERRORES*/
    if (connect(socket, (struct sockaddr *) &serverAddress, serverSize) < 0) {
        // logger info
        cout << "Error al conectar con el servidor " << strerror(errno) << endl;
        return -1;
    }
    return 0;

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


std::string chartoString (char* buffer){
    string string = "";
    for (int i = 0; i< strlen(buffer);i++){
        string = string + buffer[i];
    }
    return string;
}


void Socket::Enviar(int socket, const void *mensaje, size_t mensajeLength) {
        ssize_t totalEnviado= 0;
        ssize_t ultimaCantidadEnviada = 0;
        while (totalEnviado < mensajeLength){
            ultimaCantidadEnviada = send(socket, mensaje + totalEnviado, mensajeLength-totalEnviado, MSG_NOSIGNAL);
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


std::string Socket::Recibir(int socket, size_t mensajeAleerLength) {
    bool socketShutDown = false;
    ssize_t totalRecibido = 0;
    char buffer[MAX_DATA_SIZE];
    ssize_t ultimaCantidadRecibida = 0;
    while (totalRecibido < mensajeAleerLength && !socketShutDown) {
        ultimaCantidadRecibida = recv(socket, buffer, mensajeAleerLength - totalRecibido, 0);
        loggear(buffer, 1);
        loggear(to_string(ultimaCantidadRecibida), 1);
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


void Socket::CerrarConexion(int socket) {
    int ret = shutdown(socket, SHUT_WR);

    /*VERIFICACION DE ERRORES*/
    if (ret < 0){
        string error = strerror(errno);
        //LOGGEER INFO
        cout << "Error al cerrar conexion " << error << endl;
    }
}

void Socket::CerrarSocket(int socket) {
    //close(socket);
}

Socket::~Socket(){
}


