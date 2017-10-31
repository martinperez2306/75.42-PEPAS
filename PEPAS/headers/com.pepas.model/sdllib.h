#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../../headers/com.pepas.logger/Logger.h"



bool init(int screen_width, int screen_height, SDL_Window** window , SDL_Renderer** renderer);


void close(SDL_Renderer** renderer, SDL_Window** window);



