
#include "../com.pepas.model/sdllib.h"
#include <cmath>

class Figura{



private:

	int posx;
	int posy;


public:
    
    Figura();

    void setearFigura(int posx1, int posy1, int ancho1,int posx2, int posy2, int ancho2, SDL_Renderer* renderer,SDL_Color color);
    void setearFondo(int posx1, int posy1, int ancho1,int posx2, int posy2, int ancho2, SDL_Renderer* renderer,SDL_Color color);

    ~Figura();

};
