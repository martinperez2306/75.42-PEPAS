//
// Created by arturi on 06/11/17.
//

#ifndef CLIENTE_RIVAL_H
#define CLIENTE_RIVAL_H


class Rival {
private:
    int player;
    int PosX;
    float horizonte;
    bool dibujar, conectado;
public:
    Rival ();

    bool getDibujar();

    bool isConectado();

    void setConectado(bool conectado);

    void actualizar(int i, int i1, float i2);

    int getHorizonte();

    int getPosX();

    int getPlayer();

    void notDibujar();
};


#endif //CLIENTE_RIVAL_H
