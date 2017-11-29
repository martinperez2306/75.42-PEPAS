#include "../../headers/com.pepas.view/VistaTransicion.h"

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024


VistaTransicion::VistaTransicion()
{
    this->window = NULL;  //se usa la del controller
    this->renderer = NULL; //se usa el del controller
    background = NULL;  //ok!
    labels = NULL;//ok!
    font = NULL;//ok!
    textLabels=NULL;//ok!
    textTitle = NULL;
    textColor.r=255;textColor.g=0;textColor.b=0;//ok!

}

VistaTransicion::~VistaTransicion()
{
    //dtor
}

bool VistaTransicion::initialize(SDL_Window* window, SDL_Renderer* renderer) {

    this->window = window;
    this->renderer = renderer;
    if( TTF_Init() == -1 )
    {
        cout << "Fallo al initialize TTF" << endl;
    	return false;
    }

    return true;
}



void VistaTransicion::actualizar_scores(string nroEtapa, string usuario, string score, string total){

    map<string,scoresUsuario>::iterator it;

    //find devuelve el end si no encontro la key

    it = this->scores.find(usuario);
    //si no lo encuentra inserta un par nuevo de usuario,score
    if (it == this->scores.end()){
        scoresUsuario nuevo;
        nuevo.score1 = "---";
        nuevo.score2 = "---";
        nuevo.score3 = "---";
        nuevo.total = "---";
        this->scores.insert( pair<string,scoresUsuario>(usuario,nuevo));
    }

    it = this->scores.find(usuario);
    if (it != this->scores.end()) { // o sea si la key existe, actualiza los scores para mostrar.
        scoresUsuario scoreAProcesar = this->scores.at(usuario);
        if (nroEtapa == "1"){
            scoreAProcesar.score1 = score;
            scoreAProcesar.total = total;
        }
        if (nroEtapa == "2"){
            scoreAProcesar.score2 = score;
            scoreAProcesar.total = total;
        }
        if (nroEtapa == "3"){
            scoreAProcesar.score3 = score;
            scoreAProcesar.total = total;
        }
        scores[usuario] = scoreAProcesar;
    }
}


//antes de llamar a esta funcion tengo que hacer un actualizar_scores por c/ jugador
bool VistaTransicion::render_scores(){

    SDL_RenderClear(renderer);
    int w=0,h=0;

    background = IMG_LoadTexture(renderer,"img/flags.png");  //se le puede poner otra imagen tambien.
    if(background == NULL){
        cout << "Error al cargar el background del login" << endl;
        return false;
    }//ok!

    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rectBackground.x = 0; rectBackground.y = 0; rectBackground.w = 1024; rectBackground.h = 768;

    SDL_GetRendererOutputSize(renderer,&screenWidth,&screenHeight);
    displayRect.w=screenWidth;displayRect.h=screenHeight;displayRect.x=displayRect.y=0;

    font = TTF_OpenFont("fonts/velocidad.ttf", 26 );
    if( font == NULL )
    {
    	cout << "Error al cargar la fuente para login " << endl;
        return false;
    }


    title = TTF_RenderText_Solid( font, "Scores" , textColor ); //sacar el ??
    textTitle = SDL_CreateTextureFromSurface(renderer,title);
    SDL_QueryTexture(textTitle, NULL, NULL, &w, &h);
    textRectTitle.x=450;textRectTitle.y=200;textRectTitle.w=w;textRectTitle.h=h;

    string separador = "   ";
    string aux = "JUGADOR"+separador+"ETAPA 1"+separador+"ETAPA 2"+separador+"ETAPA 3"+separador+"TOTAL";
    const char* columnas = aux.c_str();
    labels = TTF_RenderText_Solid( font, columnas, textColor );
    textLabels = SDL_CreateTextureFromSurface(renderer,labels);
    SDL_QueryTexture(textLabels, NULL, NULL, &w, &h);
    textRect.x=50;textRect.y=250;textRect.w=w;textRect.h=h;   //LA X TIENE QUE ESTAR FIJA PARA QUE LOS MUESTRE ALINEADOS.


    SDL_RenderCopy(renderer, background, &rectBackground, &displayRect);
    SDL_RenderCopy(renderer, textTitle, NULL, &textRectTitle);
    SDL_RenderCopy(renderer, textLabels, NULL, &textRect);

    int yAux = 300; //va a ir incrementando
    map<string,scoresUsuario>::iterator it;

    separador = "      ";

    for( it = scores.begin() ; it != scores.end() ; ++it )
    {
        string nombre = it->first;
        string score1 = it->second.score1;
        string score2 = it->second.score2;
        string score3 = it->second.score3;
        string total = it->second.total;

        aux = nombre+"        "+score1+separador+score2+separador+score3+separador+total;
        const char * linea = aux.c_str();

        player = TTF_RenderText_Solid( font, linea, textColor );
        textPlayer = SDL_CreateTextureFromSurface(renderer,player);
        SDL_FreeSurface(player);
        textRectPlayer.x=50;textRectPlayer.y=yAux;textRectPlayer.w=w;textRectPlayer.h=h;
        yAux = yAux + 50;
        SDL_RenderCopy(renderer, textPlayer, NULL, &textRectPlayer);
        SDL_DestroyTexture(textPlayer);

    }

    SDL_RenderPresent(renderer);

    return 1;

}
