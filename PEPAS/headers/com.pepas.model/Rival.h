//
// Created by arturi on 06/11/17.
//

#ifndef CLIENTE_RIVAL_H
#define CLIENTE_RIVAL_H


class Rival {
private:
    int player, playerDestroy;
    int PosX;
    float horizonte;
    bool dibujar;
    double noDraw;
public:
    Rival ();

    bool getDibujar();

    void actualizar(int i, int pd, int i1, float i2);

    int getHorizonte();

    int getPosX();

    int getPlayer();

    int getDestroy();

    void notDibujar();


    int getnoDraw();

    void setnoDraw(double i);
};


#endif //CLIENTE_RIVAL_H
