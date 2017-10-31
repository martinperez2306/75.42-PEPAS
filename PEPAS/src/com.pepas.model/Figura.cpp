#include "../../headers/com.pepas.model/Figura.h"
#include <iostream>

using namespace std;

    Figura::Figura(){
            
    }



    //Funcion que setea la textura a dibujar con los puntos que le pasamos
    //Se le pasa el punto xy central inferior, ancho inferior, punto cy central superior y el ancho superior, el renderer es para que dibuje y el color
    //Esta funcion NO DIBUJA solo setea lo que se va a dibujar despues con el render. En otras palabras prepara la figura para dibujarse despues 
     void Figura::setearFigura(int posx1, int posy1, int ancho1,int posx2, int posy2, int ancho2, SDL_Renderer* renderer,SDL_Color color){

        SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a );

        int p_sup_izq_x = posx2-ancho2/2;
        int p_sup_izq_y = posy2;

        int p_sup_der_x = posx2 + ancho2/2;
        int p_sup_der_y = posy2;

        int p_inf_izq_x=posx1-ancho1/2;
        int p_inf_izq_y= posy1;

        int p_inf_der_x=posx1+ancho1/2;
        int p_inf_der_y=posy1;

        int ancho_rect;
        int posx_rect;
        SDL_Rect rect;


        if(posx1 - ancho1/2 <posx2-ancho2/2){
            this->posx = posx1-ancho1/2;

        }
        else
            this->posx = posx2-ancho2/2;

        this->posy = posy2;

        int x1;
        int x2;

        if(ancho1 == ancho2 && posx1 == posx2){
            rect= {p_sup_izq_x,posy2,ancho1,posy1-posy2+1};
            SDL_RenderFillRect(renderer,&rect);

        }else if (p_inf_izq_x >= p_sup_izq_x && p_inf_izq_x < p_sup_der_x){

    
            posx_rect = p_inf_izq_x;
            x2 = p_sup_izq_x; 
            while(x2<p_inf_izq_x){
                    SDL_RenderDrawLine(renderer,p_inf_izq_x,posy1,x2,posy2);
                    x2++;
            }

            if(p_sup_der_x <= p_inf_der_x){
                ancho_rect= p_sup_der_x - p_inf_izq_x;
                x1 = p_sup_der_x;

                while(x1<=p_inf_der_x){

                        SDL_RenderDrawLine(renderer,x1,posy1,p_sup_der_x,posy2);

                    x1++;
                }

            }else if(p_sup_der_x >= p_inf_der_x){
                ancho_rect= p_inf_der_x - p_inf_izq_x;
                x2 = p_inf_der_x;

                while(x2<=p_sup_der_x){

                        SDL_RenderDrawLine(renderer,p_inf_der_x,posy1,x2,posy2);
                    x2++;
                }
            }
            rect= {posx_rect,posy2,ancho_rect,posy1-posy2+1};
                SDL_RenderFillRect(renderer,&rect);

        }else if(p_inf_izq_x <= p_sup_izq_x && p_sup_izq_x < p_inf_der_x){
    
            posx_rect = p_sup_izq_x;
            x1 = p_inf_izq_x; 
            while(x1<p_sup_izq_x){

                        SDL_RenderDrawLine(renderer,x1,posy1,p_sup_izq_x,posy2);

                   x1++;
            }

            if(p_sup_der_x <= p_inf_der_x){
                ancho_rect= p_sup_der_x - p_sup_izq_x;
                x1 = p_sup_der_x;

                while(x1<p_inf_der_x){

                        SDL_RenderDrawLine(renderer,x1,posy1,p_sup_der_x,posy2);

                    x1++;
                }

            }else if(p_sup_der_x >= p_inf_der_x){
                ancho_rect= p_inf_der_x - p_sup_izq_x;
                x2 = p_inf_der_x;

                while(x2<p_sup_der_x){
                    SDL_RenderDrawLine(renderer,p_inf_der_x,posy1,x2,posy2);
                    x2++;
                }
            }
            rect= {posx_rect,posy2,ancho_rect,posy1-posy2+1};
                SDL_RenderFillRect(renderer,&rect);

        }else{
    
            x1 = posx1-ancho1/2;
            x2 =posx2-ancho2/2;
            while(x2<posx2+ancho2/2 && x1<posx1+ancho1/2){
                SDL_RenderDrawLine(renderer,x1,posy1,x2,posy2);

                x1++;
                x2++;

            }
            while(x1<posx1+ancho1/2){
                SDL_RenderDrawLine(renderer,x1,posy1,x2,posy2);
                x1++;
            }

            while(x2<posx2+ancho2/2){
                SDL_RenderDrawLine(renderer,x1,posy1,x2,posy2);
                x2++;
            }
        }

        // SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a );
        
        // int x1 = posx1-ancho1/2;
        // int x2 =posx2-ancho2/2;

        
        // if(ancho1 == ancho2 && posx1 == posx2){
        //     rect= {p_sup_izq_x,posy2,ancho1,posy1-posy2};
        //     SDL_RenderFillRect(renderer,&rect);
        // }else{
        //     while(x2<posx2+ancho2/2 && x1<posx1+ancho1/2){
        //         SDL_RenderDrawLine(renderer,x1,posy1,x2,posy2);

        //         x1++;
        //         x2++;

        //     }
        //     while(x1<posx1+ancho1/2){
        //         SDL_RenderDrawLine(renderer,x1,posy1,x2,posy2);
        //         x1++;
        //     }

        //     while(x2<posx2+ancho2/2){
        //         SDL_RenderDrawLine(renderer,x1,posy1,x2,posy2);
        //         x2++;
        //     }
        // }


    }

    void Figura::setearFondo(int posx1, int posy1, int ancho1,int posx2, int posy2, int ancho2, SDL_Renderer* renderer,SDL_Color color){

        this->posx = posx1-ancho1/2;
        this->posy = posy2;



        SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a );
        
        if (ancho1 == ancho2){
            SDL_Rect rect = {posx,posy,ancho1,posy1-posy2};
            SDL_RenderFillRect(renderer,&rect);
        }


    }

    // ~Figura::Figura(){

    //  }