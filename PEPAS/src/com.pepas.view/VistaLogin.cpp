#include "../../headers/com.pepas.view/VistaLogin.h"

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024

VistaLogin::VistaLogin()
{
    this->window = NULL;  //se usa la del controller
    this->renderer = NULL; //se usa el del controller
    quit = false;
    termino = false;
    background = NULL;  //ok!
    option = NULL;//ok!
    font = NULL;//ok!
    textOpt=NULL;//ok!
    input = NULL;//ok!
    textInput = NULL;//ok!
    textColor.r=255;textColor.g=255;textColor.b=255;//ok!
    typing=0;
    data="";//ok!
}

VistaLogin::~VistaLogin()
{
}

bool VistaLogin::initialize(SDL_Window* window, SDL_Renderer* renderer) {  //el init se hara en el controller

	this->window = window;  //se usa la del controller
	this->renderer = renderer; //se usa el del controller
    if( TTF_Init() == -1 )
    {
        cout << "Fallo al initialize TTF" << endl;
    	return false;
    }

    return true;
}

bool VistaLogin::load_content(const char* opcion)
{
     //a esta funcion hay que pasarle por parametro la opcion
    int w=0,h=0;
   
    background = IMG_LoadTexture(renderer,"img/background.png");
    if(background == NULL){
        cout << "Error al cargar el background del login" << endl;
        return false;
    }

    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rectBackground.x = 0; rectBackground.y = 0; rectBackground.w = 1024; rectBackground.h = 768;
    // verificar bien h y w (?)
    SDL_GetRendererOutputSize(renderer,&screenWidth,&screenHeight);
    displayRect.w=screenWidth;displayRect.h=screenHeight;displayRect.x=displayRect.y=0;

    font = TTF_OpenFont( "fonts/box.otf", 40 );
    if( font == NULL )
    {
    	cout << "Error al cargar la fuente para login " << endl;
        return false;
    }


    option = TTF_RenderText_Solid( font, opcion, textColor );
    textOpt = SDL_CreateTextureFromSurface(renderer,option);
    SDL_QueryTexture(textOpt, NULL, NULL, &w, &h);
    textRect.x=200;textRect.y=200;textRect.w=w;textRect.h=h;

    return 1;
}

void VistaLogin::handle_event(SDL_Event* event) {

    SDL_Event e = *event;
    if (e.type == SDL_QUIT) {
        quit = true;
    }
    //Special key input
    else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
       //Handle backspace
        if (e.key.keysym.sym == SDLK_BACKSPACE && data.length() > 0) {
            //lop off character
            data.pop_back();
        }
        if (e.key.keysym.sym == SDLK_RETURN) {
            termino = true;
        }
    }
    //Special text input event
    else if (e.type == SDL_TEXTINPUT) {
        //Append character
        data += e.text.text;
    }
    int w=0,h=0;
    input = TTF_RenderText_Solid( font, data.c_str(), textColor );
    textInput = SDL_CreateTextureFromSurface(renderer,input);
    SDL_QueryTexture(textInput, NULL, NULL, &w, &h);
    textRectInput.x=300;textRectInput.y=300;textRectInput.w=w;textRectInput.h=h;
}

void VistaLogin::render_present()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, &rectBackground, &displayRect);
    SDL_RenderCopy(renderer, textOpt, NULL, &textRect);
    if(data!=""){
     SDL_RenderCopy(renderer, textInput, NULL, &textRectInput);
    }

    SDL_RenderPresent(renderer);
}

void VistaLogin::clean_up()
{
    SDL_FreeSurface(option);
    SDL_DestroyTexture(textOpt);
    SDL_DestroyTexture(background);

}


bool VistaLogin::get_string(const char* opcion){

    //limpio la data anterior
    data = "";

    if(this->load_content(opcion) == false)
    {
        cout<<"Fallo el load_content en login "<<endl;
        return -1;
    }

    quit = false;
    termino = false;

    while(!quit && !termino){  //while (!quit && not terminado)
        while(SDL_PollEvent(&Event) != 0) {
            handle_event(&Event);
        }
        this->render_present();
    }//vendria a ser el main

    this->clean_up();
    SDL_FreeSurface(input);
    SDL_DestroyTexture(textInput);

    return quit;

}

string VistaLogin::get_last_input(){
    return this->data;
}


void VistaLogin::get_result(const char* information){

    //limpio la data anterior
    data = "";

    if(this->load_content(information) == false)
    {
        cout<<"Fallo el load_content en login "<<endl;
        //return -1;
    }

    this->render_present();
    usleep(3000000);

    this->clean_up();
}
