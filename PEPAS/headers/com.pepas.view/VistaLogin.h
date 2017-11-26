#ifndef VISTALOGIN_H
#define VISTALOGIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <unistd.h>

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024

using namespace std;

class VistaLogin
{
	private:
    	bool quit;
    	bool termino;
    	SDL_Window* window;
    	SDL_Renderer* renderer;
    	SDL_Event Event;
    	int screenWidth,screenHeight;
    	SDL_Rect displayRect;

    	SDL_Texture *background;
    	SDL_Rect rectBackground;

    	TTF_Font *font;
    	SDL_Surface *option;

    	SDL_Texture *textOpt;

    	SDL_Surface *input;
    	SDL_Texture *textInput;
    	SDL_Rect textRect;
    	SDL_Rect textRectInput;

    	SDL_Color textColor;

    	std::string data;
    	bool typing;

	public:
        VistaLogin();
        virtual ~VistaLogin();
        bool initialize(SDL_Window* window, SDL_Renderer* renderer);
        bool load_content(const char* opcion);
        void handle_event(SDL_Event* Event);
        void render_present();
        void clean_up();
        bool get_string(const char* opcion);
        string get_last_input();
        void get_result(const char* information);

};

#endif // VISTALOGIN_H
