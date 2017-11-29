#ifndef COM_PEPAS_VIEW_VISTATRANSICION_H_
#define COM_PEPAS_VIEW_VISTATRANSICION_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <map>

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024

using namespace std;

// sirve para almacenar los scores de cada usuario al finalizar cada etapa y mantenerlos actualizados.
struct scoresUsuario {
  string score1;
  string score2;
  string score3;
  string total;
} ;



class VistaTransicion
{

    private:

    	SDL_Window* window; //lo pasa el controller
    	SDL_Renderer* renderer; //lo pasa el controller
    	SDL_Event Event; // hace falta???
    	int screenWidth,screenHeight;

    	SDL_Rect displayRect;

    	SDL_Texture *background;
    	SDL_Rect rectBackground;

    	TTF_Font *font;
        SDL_Color textColor;

        SDL_Surface *title;
    	SDL_Texture *textTitle;
    	SDL_Rect textRectTitle;

    	SDL_Surface *labels;
    	SDL_Texture *textLabels;
    	SDL_Rect textRect;

        SDL_Surface *player;
    	SDL_Texture *textPlayer;
    	SDL_Rect textRectPlayer;

    	map<string,scoresUsuario> scores;

    public:
        VistaTransicion();
        virtual ~VistaTransicion();
        bool initialize(SDL_Window* window, SDL_Renderer* renderer);
        void clean_up();
        void actualizar_scores(string nroEtapa, string usuario, string score, string total);
        bool render_scores();

};

#endif /* COM_PEPAS_VIEW_VISTATRANSICION_H_ */
