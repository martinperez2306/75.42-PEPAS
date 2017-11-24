//
// Created by arturi on 06/11/17.
//

#include <iostream>
#include "../../headers/com.pepas.model/Rival.h"

Rival::Rival() {

    dibujar = false;

}

bool Rival::getDibujar() {
    return dibujar;
}

void Rival::actualizar(int pNum, int x, float y) {

    player = pNum;
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
