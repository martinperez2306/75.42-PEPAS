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


#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/minimapa.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/posicion.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/objetos.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/segmento.h"
#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.model/Recta.h"



using namespace std;
Class Vista{
    private:   //The window we'll be rendering to
        SDL_Window* gWindow;
        //The window renderer
        SDL_Renderer* gRenderer;
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

    void graficarMinimapa(Minimapa* minimapa);

    ~Vista();
};

#endif //COM_PEPAS_VISTA_VISTA_H
