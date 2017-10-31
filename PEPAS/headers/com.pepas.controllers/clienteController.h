/*
 * clienteController2.h
 *
 *  Created on: 6 sep. 2017
 *      Author: bigfatpancha
 */

#ifndef COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_
#define COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_


#include "../com.pepas.model/recvThread.h"
#include "../com.pepas.model/aliveSignalThread.h"
#include "../com.pepas.model/cliente.h"
#include "../com.pepas.model/Mensaje.h"
#include "../com.pepas.parser/ClienteParser.h"
#include "../com.pepas.model/sdllib.h"
#include "../com.pepas.model/Figura.h"
#include "../com.pepas.model/Textura.h"
#include "../com.pepas.model/Auto.h"
#include "../com.pepas.model/threadMinimapa.h"
#include <map>

class ClienteController{



private:

    ClienteParser* clienteParser;
    ClienteParser::SocketData socketData;
    Cliente* cliente;
    recvThread threadRecibir;
    aliveSignalThread threadEnviar;
	threadMinimapa threadGraficoMinimapa;


    bool reconexion; 
    char ipAddress[20];
    char testFile [100];

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* superficieVentana;
    Textura sky;
    Textura trees;
    Textura hills;
    Textura car;
    Textura* arbol;
    Textura* cartel;
	Textura* cartel2;

    Auto autito;

    int carPosX;
    std::map<int,Textura*>* obstaculos;



	int x;
	int y;
	int z;
    int W;
    int X;
    int Y;
    int Z;
    int pos;
    int velY;
    float scale,dx;
    int roadW;
    int segL; //segment length
    float camD; //camera depth

    bool PressUP;
    bool curveR, curveL;

    float offsetBackgroundTree;
    float offsetBackgroundHills;



public:


    ClienteController(const char* archivo);

    ClienteController(ClienteParser *ClienteParser);

    int conectarConElServidor();

    void desconectarseDelServidor();

    void logOut();

    void stressTest();


    void enviarMensajePrivado();
    void empezarRecibir();
    void dejarRecibir();


    void salirDelPrograma();

    ~ClienteController();

    Cliente *obtenerCliente();

    void obtengoPuertoNuevoYHagoConectar();;
    void logIn();
    void entrarAlChat();
    void verBuzon();

    void enviarBroadcast(string entradita);
	void conectar();
	void dibujar();

    void keyEvent(SDL_Event event);
    bool loadMedia();

    void checkCurveAndSetCentrifuga(int curve);

    void backgroundMove();
	void verMinimapa();
};

#endif /* COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_ */
