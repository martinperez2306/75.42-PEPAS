#ifndef COM_PEPAS_VISTA_VISTA_H
#define COM_PEPAS_VISTA_VISTA_H
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>
#include <stdlib.h>
//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "../com.pepas.model/minimapa.h"
#include "../com.pepas.model/posicion.h"
#include "../com.pepas.model/objetos.h"
#include "../com.pepas.model/segmento.h"
#include "../com.pepas.model/Recta.h"
#include "../com.pepas.model/Recorredor.h"

using namespace std;

class Vista{

private:   //The window we'll be rendering to
        SDL_Window* gWindow;
        //The window renderer
        SDL_Renderer* gRenderer;
        bool graficado;
        Recorredor* recorredor;

public:

       Vista();

      //Starts up SDL and creates window
        bool init();

    //Loads media
        bool loadMedia();

    //Frees media and s

    //shuts down SDL
        void close();

    //Loads individual image as texture
    SDL_Texture* loadTexture( std::string path );


    //SDL TRABAJA CON EL EJE Y INVERTIDO A LO ORDINARIO
    //VER RECORREDOR PARA ENTENDER LA LOGICA DE LOS EJES CARTESIANOS Y PUNTOS CARDINALES
    void graficarMinimapa(Minimapa* minimapa);

    bool minimapaGraficado();

    ~Vista();
};

#endif //COM_PEPAS_VISTA_VISTA_H
