//
// Created by arturi on 25/10/17.
//
#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024
#define roadW 2000

#include "../../headers/com.pepas.model/Auto.h"
Auto::Auto()
{
    //Initialize the offsets
    PosX =SCREEN_WIDTH/2 -100;
    PosY =SCREEN_HEIGHT - 180 ;
    //Initialize the velocity
    VelX = 0;
    VelY = 0;
    posicion = 0;

}




Textura Auto::getTextura() {
    return car;
}

void Auto::render(int x, int y, SDL_Renderer *renderer) {
    car.render(x,y,renderer);

}

void Auto::setTextura(Textura tex) {
    this->car = tex;

}

int Auto::getX() {
    return PosX;
}


int Auto::getY() {
    return PosY;
}


void Auto::moveLeft_KD() {
    VelX -= CAR_VEL_X;

}

void Auto::moveRight_KD() {
    VelX += CAR_VEL_X ;
}

void Auto::moveLeft_KU() {
    VelX += CAR_VEL_X;
}

void Auto::moveRight_KU() {
    VelX -= CAR_VEL_X;
}

void Auto::calculateMove(bool PressUP, bool curveR, bool curveL) {

    //cout <<"posY "<<posicion<<endl;
    //cout <<"velY "<<VelY<<endl;

   // cout <<"posx "<<PosX<<endl;

    //cout <<"velX "<<VelX<<endl;

    PosX += VelX;



    if (VelY >= VEL_MAX/2 && curveL && PosX < SCREEN_WIDTH - CAR_WIDTH){
        PosX += DESVIO;
    }else if (VelY >= VEL_MAX/2 && curveR && PosX > 0){
        PosX -= DESVIO;

    }
    else if( ( PosX < 0 ) || ( PosX + CAR_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        PosX -= VelX;
    }

    /*No excedo la velocidad maxima*/
    if (VelY > VEL_MAX)
        VelY = VEL_MAX;
    else if (VelY < VEL_MIN )
        VelY = VEL_MIN;

    /*Desacelera automaticamente*/
    if (VelY>VEL_MIN && VelY < VEL_MAX && !PressUP) {
        VelY -= DESACELERAR;

    }
    /*Evito que salga de la pantalla*/
    if( ( PosY < 0 ) || ( PosY + CAR_HEIGHT > SCREEN_HEIGHT ) )
    {
        posicion -= VelY;
    }

    if (PressUP && VelY < VEL_MAX) {
        VelY += CAR_VEL;
    }

    posicion += VelY;

}

void Auto::moveUP_KD(int pos) {

    VelY += CAR_VEL;
    if (VelY>VEL_MAX){
        VelY = VEL_MAX;
    }
    posicion = pos;


}

void Auto::moveDown_KD(int pos) {
    VelY -= CAR_VEL;
    if (VelY < VEL_MIN)
        VelY = VEL_MIN;
    posicion = pos;
}

void Auto::moveUP_KU(int pos) {
    VelY -= CAR_VEL;
    posicion = pos;

}

void Auto::moveDown_KU(int pos) {
    VelY -= CAR_VEL;
    posicion = pos;

}

int Auto::getPosition() {
    return posicion;
}

bool Auto::isMoving() {
    bool move;
    if (VelY>0)
        move = true;
    else move = false;
    return move ;
}






