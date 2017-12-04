//
// Created by arturi on 06/11/17.
//

#include <iostream>
#include "../../headers/com.pepas.model/Rival.h"

Rival::Rival() {


    dibujar = false;
    noDraw = 0;

}

bool Rival::getDibujar() {
    return dibujar;
}

void Rival::actualizar(int pNum, int destroy, int x, float y) {

    player = pNum;
    playerDestroy = destroy;
    PosX = x;
    horizonte = y;
    dibujar = true;
}

int Rival::getHorizonte() {
    return horizonte;
}

int Rival::getPosX() {
    return PosX;
}

int Rival::getPlayer() {
    return player;
}

void Rival::notDibujar() {
    dibujar = false;

}

int Rival::getDestroy() {
    return playerDestroy;
}

int Rival::getnoDraw() {
    return noDraw;
}

void Rival::setnoDraw(double i) {
    noDraw = i;
}

void Rival::setDibujar() {
    dibujar = true;
}
