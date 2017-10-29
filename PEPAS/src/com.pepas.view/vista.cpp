//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "../../headers/com.pepas.model/minimapa.h"
#include "../../headers/com.pepas.model/posicion.h"
#include "../../headers/com.pepas.model/objetos.h"
#include "../../headers/com.pepas.model/segmento.h"
#include "../../headers/com.pepas.model/Recta.h"

#include "../../headers/com.pepas.view/vista.h"
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

Vista::Vista(){

	this->gWindow=NULL;
	this->gRenderer =NULL;
	this->graficado = false;
	this->recorredor = new Recorredor();
}

bool Vista::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		this->gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( this->gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			this->gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( this->gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Vista::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void Vista::close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Vista::minimapaGraficado(){
	return this->graficado;
}

SDL_Texture* Vista::loadTexture( std::string path )
{
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
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(this->gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void Vista::graficarMinimapa(Minimapa* minimapa){
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			this->graficado = true;
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				///////////////////
				list<Segmento*>* ruta = minimapa->getRuta();
				for(list<Segmento*>::iterator it=ruta->begin(); it!=ruta->end();++it){
					Segmento* segm = *it;
					int X1 = (segm->getPosicionInicial()->getX()/10);
					int Y1 = (segm->getPosicionInicial()->getY()/10);
					int Y2 = (segm->getPosicionFinal()->getY()/10);
					int X2 = (segm->getPosicionFinal()->getX()/10);
					///Pinto pista
					SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
					SDL_RenderDrawLine( gRenderer,X1,Y1,X2,Y2);

				}
				list<Objeto*>* objetos = minimapa->getObjetos();
				for(list<Segmento*>::iterator it=ruta->begin(); it!=ruta->end();++it){
					Segmento* segm = *it;
					this->recorredor->recorrer(segm,objetos);

				}
				list<Posicion*>* posicionesDeLosObjetos = this->recorredor->getPosicionesDeLosObjetos();
				for(list<Posicion*>::iterator it = posicionesDeLosObjetos->begin() ; it!= posicionesDeLosObjetos->end(); ++it){
					Posicion* pos = *it;
					int x = (pos->getX() / 10);
					int y = (pos->getY() / 10);
					cout<<x<<endl;
					cout<<y<<endl;
					///Pinto objeto
					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
					SDL_RenderDrawPoint(gRenderer,x,y);
				}

//				//Draw vertical line of yellow dots
//				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
//                SDL_RenderDrawPoint( gRenderer, 200, 200 );
//
//
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	this->graficado = false;
	close();
}
