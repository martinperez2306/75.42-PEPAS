//
// Created by arturi on 25/10/17.
//

#include <SDL2/SDL_image.h>
#include "../../headers/com.pepas.model/Textura.h"

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024


Textura::Textura()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Textura::~Textura()
{
    free();
}



void Textura::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Textura::render( int x, int y, SDL_Renderer* renderer ) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    //Render to screen
    SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

void Textura::render( int x, int y,int w,int h, SDL_Renderer* renderer ) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, w, h};

    //Render to screen
    SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

int Textura::getWidth()
{
    return mWidth;
}

int Textura::getHeight()
{
    return mHeight;
}



bool Textura::loadFromFile( std::string path, SDL_Renderer* renderer )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool Textura::loadFromRenderedText( std::string textureText, SDL_Color textColor,TTF_Font *font,SDL_Renderer* renderer)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    
    //Return success
    return mTexture != NULL;
}