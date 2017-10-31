//
// Created by arturi on 25/10/17.
//

#ifndef INC_75_42_PEPAS_TEXTURA_H
#define INC_75_42_PEPAS_TEXTURA_H


#include <SDL2/SDL_render.h>
#include <string>

class Textura {
private:

    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;

    public:

    Textura();

    ~Textura();

    void free();

    void render( int x, int y, SDL_Renderer* renderer);
void render( int x, int y,int w,int h, SDL_Renderer* renderer );

    bool loadFromFile(std::string path, SDL_Renderer* renderer);

    int getWidth();
    int getHeight();



    };





#endif //INC_75_42_PEPAS_TEXTURA_H
