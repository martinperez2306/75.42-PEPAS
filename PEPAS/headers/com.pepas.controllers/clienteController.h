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
#include "../com.pepas.model/minimapa.h"
#include "../com.pepas.model/posicion.h"
#include "../com.pepas.model/objetos.h"
#include "../com.pepas.model/segmento.h"
#include "../com.pepas.model/Recta.h"
#include "../com.pepas.model/Recorredor.h"
#include <SDL2/SDL_ttf.h>
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
    Textura* car;
    Textura* arbol;
    Textura* cartel;
    Textura* cartel2;
    TTF_Font *font;
    Textura* opcion;
    Textura* ingreso;
	Textura* player1;
    Textura* player2;
    Textura* player3;
	Textura* player4;

    Auto* autito;

    int carPosX, curveSet;
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
    void logIn(string usuario, string clave);
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
    void procesarMensajePosicion(int pos, int x);
    bool getString(string* str,string optText);
    string agregarPadding(int i);
    void enviarMoveUp();

    void enviarMoveDown();

    void enviarMoveLeft();

    void enviarMoveRight();

    void enviarNotMoveUp();

    void enviarNotMoveDown();

    void enviarNotMoveLeft();

    void enviarNotMoveRight();

	void actualizarMinimapa(Minimapa* minimapa);

	void carAsign();

    Textura *getTextura(int i);
};

#endif /* COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_ */
