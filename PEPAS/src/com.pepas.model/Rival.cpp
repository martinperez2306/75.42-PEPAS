//
// Created by arturi on 06/11/17.
//

#include "../../headers/com.pepas.model/Rival.h"

Rival::Rival() {

    dibujar = false;

}

bool Rival::getDibujar() {
    return dibujar;
}

void Rival::actualizar(int pNum, int x, int y) {
    player = pNum;
    PosX = x;
    horizonte = y;
    dibujar = true;
}

bool Rival::isConectado() {
	return conectado;
}

void Rival::setConectado(bool conectado) {
	conectado = conectado;
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
