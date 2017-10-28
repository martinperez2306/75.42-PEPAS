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

#include "/home/barbarasanchez/Desktop/75.42-PEPAS-cliente/PEPAS/headers/com.pepas.view/vista.h"
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Vista::Vista(){

	this->gWindow=NULL;
	this->gRenderer =NULL;

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
                map<Segmento*,Objetos*>* mapa=minimapa->getMinimapa();
				for (map<Segmento*,Objetos*>::iterator it=mapa->begin(); it!=mapa->end(); ++it){
        			int X1= it->first->getPosicionInicial()->getX();
         			int Y1 =it->first->getPosicionInicial()->getY();
        			int X2= it->first->getPosicionFinal()->getX();
         			int Y2= it->first->getPosicionFinal()->getY();
        			int derecha=it->second->getObjetoDerecha();
         			int izquierda=it->second->getObjetoIzquierda();
        			Recta* recta= new Recta();
         			recta->calcularEcuacionDeLaRecta(X1,Y1,X2,Y2);
         			int pendiente=recta->getA();
        			 ///Pinto pista
         			 SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
        			 SDL_RenderDrawLine( gRenderer,X1,Y1,X2,Y2);

        			if(X1>X2 || Y1<Y2){
            			int aux ;
            			aux=X1;
           				X1=X2;
           				X2=aux;
           				aux=Y1;
           				Y1=Y2;
           				Y2=aux;
        			}
        			 ////pinto objetos a los lados////
         			switch(pendiente){
         				case 0:
                   			 if(derecha =2){
                   			 	SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
								SDL_RenderDrawLine( gRenderer,X1,Y1-1,X2,Y2-1);
                    		}
                   			 if (derecha !=2 && derecha >2){
                   			 	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                        		SDL_RenderDrawLine( gRenderer,X1,Y1-1,X2,Y2-1);
                    		}
                 		  	if(izquierda =2){
                 		  		SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                       			 SDL_RenderDrawLine( gRenderer,X1,Y1+1,X2,Y2+1);
                   			}
                   			 if (izquierda !=2 && izquierda >2){
                   			 	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                       			 SDL_RenderDrawLine( gRenderer,X1,Y1+1,X2,Y2+1);
                    		}
               		 		break;
            			case 1:
                 			   if(derecha =2){
                 			   	SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                      				  SDL_RenderDrawLine( gRenderer,X1+1,Y1-1,X2+1,Y2-1);
                   				 }
                   				 if (derecha !=2 && derecha >2){
                   				 	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                      					SDL_RenderDrawLine( gRenderer,X1+1,Y1-1,X2+1,Y2-1);
                   				 }
                    			if(izquierda =2){
                    				SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                     			   SDL_RenderDrawLine( gRenderer,X1-1,Y1+1,X2-1,Y2+1);
                   				 }
                    			if (izquierda !=2 && izquierda >2){
                    				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                       				 SDL_RenderDrawLine( gRenderer,X1-1,Y1+1,X2-1,Y2+1);
                    			}
                			break;
            			case -1:
                 				  if(derecha =2){+
                 				  	SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                      				  SDL_RenderDrawLine( gRenderer,X1+1,Y1+1,X2+1,Y2-1);
                   				 }
                    			if (derecha !=2 && derecha >2){
                    				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                      				  SDL_RenderDrawLine( gRenderer,X1+1,Y1+1,X2+1,Y2-1);
                    			}
                    			if(izquierda =2){
                    				SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                       				 SDL_RenderDrawLine( gRenderer,X1-1,Y1-1,X2-1,Y2-1);
                   				 }
                   				 if (izquierda !=2 && izquierda >2){
                   				 	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                      				  SDL_RenderDrawLine( gRenderer,X1-1,Y1-1,X2-1,Y2-1);
                  				  }
                			break;
            			case 2147483647:
                 			   if(derecha =2){
                 			   	SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                      				  SDL_RenderDrawLine( gRenderer,X1+1,Y1,X2+1,Y2);
                    			}
                    			if (derecha !=2 && derecha >2){
                    				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                       				 SDL_RenderDrawLine( gRenderer,X1+1,Y1,X2+1,Y2);
                   				 }
                   				 if(izquierda =2){
                   				 	SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                      				  SDL_RenderDrawLine( gRenderer,X1-1,Y1,X2-1,Y2);
                    			}
                   				 if (izquierda !=2 && izquierda >2){
                   				 	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
                      				  SDL_RenderDrawLine( gRenderer,X1-1,Y1,X2-1,Y2);
                  				 }
                			break;
        			}

   				 }
				/////////////////

				//Draw vertical line of yellow dots
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
                SDL_RenderDrawPoint( gRenderer, 200, 200 );


				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

}
