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
#include"../com.pepas.view/VistaTransicion.h"
#include <SDL2/SDL_ttf.h>
#include <map>
#include <SDL2/SDL_mixer.h>
#include "../com.pepas.view/VistaLogin.h"
#include <vector>
#include <ctime>
#include <cstdlib>


class ClienteController{



private:

    ClienteParser* clienteParser;
    ClienteParser::SocketData socketData;
    Cliente* cliente;
    recvThread threadRecibir;
    aliveSignalThread threadEnviar;
	threadMinimapa threadGraficoMinimapa;
    VistaTransicion* vistaTransicion;


    bool reconexion, moving;
    char ipAddress[20];
    char testFile [100];
	int posMoving;

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
    TTF_Font *login;
    TTF_Font *speed;
    TTF_Font *tiempo;
    TTF_Font *score;
    Textura* opcion;
    Textura* ingreso;
	Textura* player1;
    Textura* player2;
    Textura* player3;
	Textura* player4;
	Textura* player5;

	Textura* player1_1;
	Textura* player1_2;
	Textura* player1_3;

	Textura* player2_1;
	Textura* player2_2;
	Textura* player2_3;

	Textura* player3_1;
	Textura* player3_2;
	Textura* player3_3;

	Textura* player4_1;
	Textura* player4_2;
	Textura* player4_3;






	Auto* autito;

    Mix_Music *soundTrack = NULL;

    Mix_Chunk *gUp = NULL;
    Mix_Chunk *gLeft = NULL;
    Mix_Chunk *gRight = NULL;
    Mix_Chunk *gBreak = NULL;
    Mix_Chunk *gLeave = NULL;

    int carPosX;
    double curveSet;
    std::map<int,Textura*>* obstaculos;

    bool mapaCargado;

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

    VistaLogin* vistaLogin;

    struct Line {
                   double x, y, z; //3d center of line
                   double X, Y, W; //screen coord
                   double scale;
                   double camD = 0.5;
                   double roadW = 2000;
                   double curve, spriteX, clip, spriteX2, spriteXR1, spriteXR2, spriteXR3, spriteXR4,spriteXR5;
                   Textura *sprite;
                   Textura *sprite2;
                   Textura *spriteR1;
                   Textura *spriteR2;
                   Textura *spriteR3;
                    Textura * spriteR4;
                    Textura * spriteR5;

                   Line() {
                       spriteX = spriteX2 = x = y = z = 0;
                       sprite = NULL;
                       sprite2 = NULL;
                       spriteR1 = NULL;
                       spriteR2 = NULL;
                       spriteR3 = NULL;
                       spriteR4 = NULL;
                       spriteR5 = NULL;
                       spriteXR1 = 0;
                       spriteXR2 = 0;
                       spriteXR3 = 0;
                       spriteXR4 = 0;
                       spriteXR5 = 0;
                   }

                   void project(int camX, int camY, int camZ) {
                       scale = camD / (z - camZ);
                       X = (1 + scale * (x - camX)) * SCREEN_WIDTH / 2;
                       Y = ((1 - scale * (y - camY)) * SCREEN_HEIGHT / 2);
                       W = scale * (roadW) * SCREEN_WIDTH / 2;

                   }

                   void drawSprite(SDL_Renderer *renderer) {
                       if (spriteX != 0) {
                           int w = sprite->getWidth();
                           int h = sprite->getHeight();

                           double destX = X + scale * spriteX * SCREEN_WIDTH / 2;//* SCREEN_WIDTH/2
                           double destY = Y + 4;
                           double destW = w * W / 266;
                           double destH = h * W / 266;

                           destX += destW * spriteX; //offsetX
                           destY += destH * (-1);    //offsetY

                           SDL_RenderSetScale(renderer, destW / w, destH / h);
                           sprite->render(destX / destW * w, destY * h / destH, renderer);
                           SDL_RenderSetScale(renderer, 1, 1);
                       }

                       if (spriteX2 != 0) {
                           int w = sprite2->getWidth();
                           int h = sprite2->getHeight();

                           double destX = X + scale * spriteX2 * SCREEN_WIDTH / 2;
                           double destY = Y + 4;
                           double destW = w * W / 266;
                           double destH = h * W / 266;

                           destX += destW * spriteX2; //offsetX
                           destY += destH * (-1);    //offsetY


                           SDL_RenderSetScale(renderer, destW / w, destH / h);
                           sprite2->render(destX / destW * w, destY * h / destH, renderer);
                           SDL_RenderSetScale(renderer, 1, 1);
                       }
                       if (spriteXR1 != 0) {
                           int w = spriteR1->getWidth();
                           int h = spriteR1->getHeight();

                           double destX = X + scale * spriteXR1 * SCREEN_WIDTH / 2;
                           double destY = Y + 4;
                           double destW = w * W / 700;
                           double destH = h * W / 700;

                           destX += destW * spriteXR1;
                           destY += destH * (-1);


                           SDL_RenderSetScale(renderer, destW / w, destH / h);
                           spriteR1->render(destX / destW * w, destY * h / destH, renderer);
                           SDL_RenderSetScale(renderer, 1, 1);
                       }
                       if (spriteXR2 != 0) {
                           int w = spriteR2->getWidth();
                           int h = spriteR2->getHeight();

                           double destX = X + scale * spriteXR2 * SCREEN_WIDTH / 2;
                           double destY = Y + 4;
                           double destW = w * W / 700;
                           double destH = h * W / 700;

                           destX += destW * spriteXR2; //offsetX
                           destY += destH * (-1);    //offsetY


                           SDL_RenderSetScale(renderer, destW / w, destH / h);
                           spriteR2->render(destX / destW * w, destY * h / destH, renderer);
                           SDL_RenderSetScale(renderer, 1, 1);
                       }
                       if (spriteXR3 != 0) {
                           int w = spriteR3->getWidth();
                           int h = spriteR3->getHeight();

                           double destX = X + scale * spriteXR3 * SCREEN_WIDTH / 2;
                           double destY = Y + 4;
                           double destW = w * W / 730;
                           double destH = h * W / 730;

                           destX += destW * spriteXR3;
                           destY += destH * (-1);

                           SDL_RenderSetScale(renderer, destW / w, destH / h);
                           spriteR3->render(destX / destW * w, destY * h / destH, renderer);
                           SDL_RenderSetScale(renderer, 1, 1);
                       }
                       if (spriteXR4 != 0) {
                           int w = spriteR1->getWidth();
                           int h = spriteR1->getHeight();

                           double destX = X + scale * spriteXR4 * SCREEN_WIDTH / 2;
                           double destY = Y + 4;
                           double destW = w * W / 700;
                           double destH = h * W / 700;

                           destX += destW * spriteXR4;
                           destY += destH * (-1);


                           SDL_RenderSetScale(renderer, destW / w, destH / h);
                           spriteR4->render(destX / destW * w, destY * h / destH, renderer);
                           SDL_RenderSetScale(renderer, 1, 1);
                       }
                       if (spriteXR5 != 0) {
                           int w = spriteR5->getWidth();
                           int h = spriteR5->getHeight();

                           double destX = X + scale * spriteXR5 * SCREEN_WIDTH / 2;
                           double destY = Y + 4;
                           double destW = w * W / 700;
                           double destH = h * W / 700;

                           destX += destW * spriteXR5;
                           destY += destH * (-1);


                           SDL_RenderSetScale(renderer, destW / w, destH / h);
                           spriteR5->render(destX / destW * w, destY * h / destH, renderer);
                           SDL_RenderSetScale(renderer, 1, 1);
                       }
                   }
               };

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
    void checkCurveAndSetCentrifuga(double curve);
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

	void cargarMapa(std::vector<Line>* lines);

	void carAsign();

	void dibujarRival(double X,double Y,double W, double scale, double spriteX, Textura* sprite);

    Textura *getTextura(Rival* i);
    void renderVelocidad();
    void renderTiempo(string tiempo);
    void renderDistancia(int posMoving);


    void enviarPressEnter();
};

#endif /* COM_PEPAS_CONTROLLERS_CLIENTECONTROLLER_H_ */
