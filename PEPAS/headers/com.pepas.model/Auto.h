//
// Created by arturi on 25/10/17.
//

#ifndef INC_75_42_PEPAS_AUTO_H
#define INC_75_42_PEPAS_AUTO_H


#include <SDL2/SDL.h>
#include "Textura.h"
#include <iostream>
using namespace std;

class Auto {
private:

    float PosX, PosY, posicion;
    float VelX, VelY;


public:

    static const int CAR_WIDTH = 200;
    static const int CAR_HEIGHT = 103;

    float CAR_VEL = 0.2;
    float CAR_VEL_X =  0.5;
    float DESACELERAR = 0.1;
    float DESVIO = 0.3; // desvio en curvas
    int VEL_MAX = 50;
    int VEL_MIN = 0;




    Auto();

    int getX();

    int getY();

    void moveLeft_KD();

    void moveRight_KD();

    void moveLeft_KU();

    void moveRight_KU();

    void moveUP_KD(int pos);

    void moveDown_KD(int pos);

    void moveUP_KU(int pos);

    void moveDown_KU(int pos);

    int getPosition();

    bool isMoving();

    void calculateMove(bool PressUP, bool curveR, bool curveL);
};


#endif //INC_75_42_PEPAS_AUTO_H
