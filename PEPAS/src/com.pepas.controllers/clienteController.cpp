//
// Created by florencia on 03/09/17.
//

#include <iomanip>
#include "../../headers/com.pepas.controllers/clienteController.h"
#include <zconf.h>
#include <vector>

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024


ClienteController::ClienteController(const char* archivo){
    this->socketData = this->clienteParser->parsearXML(archivo);
	this->cliente= new Cliente();
	this->threadRecibir = recvThread(cliente);
	this->threadEnviar = aliveSignalThread(cliente);
	this->reconexion = false;
	strcpy(this->ipAddress,socketData.ip);
	cout<<"asdasdsa"<<ipAddress<<endl;
	cout<<"qweqwewq"<<socketData.ip<<endl;
	strcpy(this->testFile ,socketData.rutafile);
    this->threadGraficoMinimapa=threadMinimapa(cliente);

	SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    int velX = Y;

    this->obstaculos = new map<int,Textura*>();
    this->ingreso = new Textura();
    this->opcion = new Textura();

     PressUP = false;
    offsetBackgroundTree = -1000;
    offsetBackgroundHills = -1000;





}


ClienteController::ClienteController(ClienteParser *clientePaser) {
	this->clienteParser = clientePaser;

}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)


void ClienteController::conectar(){

	if(this->cliente->estaConectado()){
		cout<< "Usted ya esta conectado" <<endl;
		return;
	}
	
	//Esto es para cerrar el thread de la conexion anterior.
	if(reconexion){
		this->dejarRecibir();
		reconexion = false;
	}
	if (this->conectarConElServidor() == -1) {
		cout<<"Ocurrio un error al intentar conectarse, intente nuevamente"<<endl;
	} else {
        cout<<"Haciendo cambio de puerto"<<endl;
		this->obtengoPuertoNuevoYHagoConectar();
        //this->verMinimapa();


	}
}


int ClienteController::conectarConElServidor(){
	return this->cliente->conectarseAlServidor(this->ipAddress, socketData.puerto);
}




void ClienteController::desconectarseDelServidor(){
	if(!this->cliente->estaConectado()){
		cout << "Usted no esta conectado" << endl;
		return;
	}
	 if (cliente->estalogueado()){
	 	this->logOut();
	 }

	this->cliente->desconectarse();
	this->obtenerCliente()->obtenerSocket()->CerrarConexion(this->obtenerCliente()->obtenerSocketFD());
    //this->obtenerCliente()->obtenerSocket()->CerrarSocket(this->obtenerCliente()->obtenerSocketFD());
	reconexion = false;
	this->dejarRecibir();
	this->cliente->vaciarColaChat();
	this->cliente->vaciarColaBuzon();


	cout<< "Se ha desconectado" << endl;

}



void ClienteController::logOut() {
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para desloguearse"<< endl;
		return;
	}

	this->obtenerCliente()->desloguearse();
	string usuario = this->obtenerCliente()->obtenerUsuario()->getNombre();
	this->obtenerCliente()->enviarMensaje(this->obtenerCliente()->procesarMensaje(usuario));
	this->obtenerCliente()->vaciarColaChat();
	this->obtenerCliente()->vaciarColaBuzon();


}

void ClienteController::logIn(string usuario, string clave) {
	if(!this->cliente->estaConectado()){
		cout<< "Debe conectarse para loguearse" <<endl;
		return;
	}

	if(cliente->estalogueado()){
        cout << "Usted ya esta logueado" << endl;
        return;
    }
	
	this->cliente->logIn(usuario, clave);

	if (this->cliente->estalogueado()){
		this->empezarRecibir();
	}

}


void ClienteController::stressTest(){
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para enviar un mensaje"<< endl;
		return;
	}
	string milisegundos, totalmili;
	cout<<"Ingrese cantidad de milisegundos entre mensajes: ";
	int mili, total;
	bool valido = true;

	try {
		cin >> milisegundos;
		mili = stoi(milisegundos, nullptr, 10);
		mili = mili * 1000;
		cout << "Ingrese cantidad de milisegundos en total: ";
		cin >> totalmili;
		total = stoi(totalmili, nullptr, 10);
		total = total * 1000;
		//multiplo = total % mili;
		if (total%mili != 0){
			valido = false;
			cout<<"Datos ingresados invalidos, deben ser multiplo"<<endl;
			loggear("Datos ingresados invalidos, deben ser multiplo",1);
		}
	} catch (std::invalid_argument) {
		cout << "Ingrese unicamente un numero " << '\n';
	}

	ifstream myReadFile;
	myReadFile.open(testFile); //this->clienteParser->obtenerRutaTestFile() 
	string stressMsg;
	if (myReadFile.is_open() && valido) {
		while (!myReadFile.eof()) {
			getline(myReadFile,stressMsg);
			myReadFile.ignore();
		}
	}
	myReadFile.close();

	int i=0;
	if (valido) {
		do {
			usleep(mili);
			enviarBroadcast(stressMsg);
			i += mili;

		} while (i != total);
	}



}





void ClienteController::enviarMensajePrivado(){
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para enviar un mensaje"<< endl;
		return;
	}
	string texto, mensajeProcesado, destinatario, bug;
    cout<<this->obtenerCliente()->obtenerUsuario()->getNombre()<<" ingresa el mensaje: ";
	//TODO aca hay un bug que no lo entiendo, si no pongo las variables de esta forma anda mal.
	getline (cin,bug);
	getline(cin, texto);
	cout<<"Ingresa el ususario destino: ";
	cin >> destinatario;
	Mensaje *mensaje = new Mensaje(Mensaje::PRIVATE_MSG, texto, this->obtenerCliente()->obtenerUsuario()->getNombre(), destinatario);
	mensajeProcesado = this->obtenerCliente()->procesarMensaje(mensaje);
	this->obtenerCliente()->enviarMensaje(mensajeProcesado);


}

void ClienteController::salirDelPrograma() {
	cout<<"SALISTE"<<endl;
	
}

ClienteController::~ClienteController(){
    delete this->cliente;
}

Cliente *ClienteController::obtenerCliente() {
    return this->cliente;
}


void ClienteController::obtengoPuertoNuevoYHagoConectar() {
	/*Recibo 4 bytes en donde ya se que voy a recibir 4 bytes con el puerto nuevo*/
	string puerto = this->obtenerCliente()->obtenerSocket()->Recibir(this->obtenerCliente()->obtenerSocketFD(), 4);
	if (puerto =="0005"){
		cout<< "El servidor ya esta ocupado con su maxima capacidad" << endl;
		return;
	}
	/*Cierro la conexion con el puerto del xml*/
	cout<<"El puerto recibido es: "<<puerto<<endl;
	this->obtenerCliente()->obtenerSocket()->CerrarConexion(this->obtenerCliente()->obtenerSocketFD());

	/*Me conecto al nuevo servidor*/
	this->obtenerCliente()->conectarseAlServidor(this->ipAddress, stoi(puerto,nullptr,10));
	cout<<"Conectado satisfactorio con puerto: "<<puerto<<endl;
	this->cliente->conectarse();
	this->empezarRecibir();
	this->reconexion = true;

}

void ClienteController::empezarRecibir(){
	this->threadRecibir.start();
    this->threadEnviar.start();
}

void ClienteController::dejarRecibir(){
	this->threadEnviar.join();
	this->threadRecibir.join();
    
}




int kbhit()
{
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
	select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &fds);
}


void ClienteController::entrarAlChat() {
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para enviar un mensaje"<< endl;
		return;
	}

	//system("clear");
	cout<<"Presione & para salir del chat"<<endl;
	string entrada("");
	cin.ignore();

	do{

		while (!this->obtenerCliente()->obtenerColaChat().empty()){
			if (kbhit()){
				break;
			}
            cout<<this->obtenerCliente()->obtenerColaChat().front()<<flush<<endl;
			this->obtenerCliente()->desencolarColaChat();
		}

		if (kbhit()){
			getline(cin,entrada);
			cout<<"\e[A";
			if(entrada.compare("&\0") == 0)
				break;
			enviarBroadcast(entrada);
		}
	}while(cliente->estalogueado());
}





void ClienteController::verBuzon() {
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para ver el buzon"<< endl;
		return;
	}

	this->obtenerCliente()->verBuzon();
}


void ClienteController::enviarBroadcast(string entrada) {

	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para enviar un mensaje"<< endl;
		return;
	}
	string mensajeProcesado;
	string destinatario = "";
	Mensaje *mensaje = new Mensaje(Mensaje::BROADCAST_MSG, entrada, this->obtenerCliente()->obtenerUsuario()->getNombre(), destinatario);
	mensajeProcesado = this->obtenerCliente()->procesarMensaje(mensaje);
	this->obtenerCliente()->enviarMensaje(mensajeProcesado);
}


void ClienteController::dibujar(){

	if( !init(SCREEN_WIDTH,SCREEN_HEIGHT,&(this->window), &(this->renderer) ))
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			
			string usuario;
			string password;

			

			//Enable text input
			SDL_StartTextInput();
			this->conectar();
			do{
				quit = getString(&usuario,"Usuario :");

				if(!quit)
					quit = getString(&password,"Clave :");

				if (!quit)
					this->logIn(usuario,password);

			sleep(1);
			}while(!this->cliente->estalogueado() && !quit);

			
			//Disable text input
			SDL_StopTextInput();


            SDL_Color gris = {0xA3,0xA3,0xA3,0xFF};
            SDL_Color grisOscuro = {0xA0,0xA0,0xA0,0xFF};
			SDL_Color verde = {0x00,0xCC,0x00,0xFF};
            SDL_Color verdeOscuro = {0x00,0x99,0x00,0xFF};
            SDL_Color blanco = {0xFF,0xFF,0xFF,0xFF};
            SDL_Color rojo = {0xFF,0x00,0x00,0xFF};
            SDL_Color transparente = {0x00,0x00,0x00,0x00};

			Figura* pista = new Figura();
			Figura* fondo = new Figura();
            Figura* line = new Figura();
            Figura* clip = new Figura();

            int maxy = SCREEN_HEIGHT;

            roadW = 2000;
            segL = 200; //segment length
            camD = 0.84f; //camera depth

             x = 0;
			 y = 0;
			 z = 0;


            struct Line
            {
                    float x,y,z; //3d center of line
                    float X,Y,W; //screen coord
                    float scale;
                    float camD = 0.5;
                    float roadW= 2000;
					float curve,spriteX,clip,spriteX2;
                    Textura* sprite;
                    Textura* sprite2;

                    Line() {spriteX=spriteX2=curve=x=y=z=0;
                    		sprite = NULL;
                    		sprite2 = NULL;}

                    void project(int camX,int camY,int camZ) {
                        scale = camD/(z-camZ);
                        X = (1 + scale*(x - camX)) * SCREEN_WIDTH/2;
                        Y = ((1 - scale*(y - camY)) * SCREEN_HEIGHT/2);
                        W = scale * (roadW)* SCREEN_WIDTH/2 ;

                    }

                    void drawSprite(SDL_Renderer* renderer){
					    if (!sprite)
					    	return;
					    
					    if(spriteX != 0){
						    int w = sprite->getWidth();
						    int h = sprite->getHeight();

						    float destX = X + scale * spriteX * SCREEN_WIDTH/2;//* SCREEN_WIDTH/2
						    float destY = Y + 4;
						    float destW  = w * W / 266;
						    float destH  = h * W / 266;

						    destX += destW * spriteX; //offsetX
						    destY += destH * (-1);    //offsetY




						    SDL_RenderSetScale(renderer,destW/w,destH/h);
						    sprite->render(destX/ destW*w,destY*h/destH,renderer);
						    SDL_RenderSetScale(renderer,1,1);
					    }

					    if(spriteX2 != 0){
						    int w = sprite2->getWidth();
						    int h = sprite2->getHeight();

						    float destX = X + scale * spriteX2 * SCREEN_WIDTH/2 ;
						    float destY = Y + 4;
						    float destW  = w * W / 266;
						    float destH  = h * W / 266;

						    destX += destW * spriteX2; //offsetX
						    destY += destH * (-1);    //offsetY


						    SDL_RenderSetScale(renderer,destW/w,destH/h);
						    sprite2->render(destX/ destW*w,destY*h/destH,renderer);
						    SDL_RenderSetScale(renderer,1,1);
					    }
					    

    				}
};

            std::vector<Line> lines;

            //list<pair<int, float>> Track; /*distancia , curvatura*/


          /*  Track.emplace_back(make_pair(500, -1));
            Track.emplace_back(make_pair(500,1));
            Track.emplace_back(make_pair(700,0)); // al ultimo segmento le agrego un offset de la perspectiva*/
            obstaculos->emplace(50,cartel);
            obstaculos->emplace(-50,cartel);
            obstaculos->emplace(-75,cartel2);
            obstaculos->emplace(75,cartel2);
            obstaculos->emplace(300,arbol);
            obstaculos->emplace(-100,arbol);
            obstaculos->emplace(100,arbol);


            std::map<int,Textura*>::iterator it_obst;

            list<pair<int, float>> Track  = this->cliente->obtenerTrack(); //TODO anda igual


            /*Armo la pista*/
            int iter_anterior = 0;
            for (auto it=Track.begin(); it !=Track.end(); it++) {
                int iteraciones = it->first;
                cout<<iteraciones<<endl;
                for (int i = iter_anterior; i < iteraciones + iter_anterior; i++) {
                    Line line;
                    line.z = i * segL;
                    line.curve = it->second;
                    it_obst = obstaculos->find(i);
                    if(it_obst != obstaculos->end()){
                    	line.sprite = it_obst->second;
                    	line.spriteX = -0.375 + (float)SCREEN_WIDTH/(5*(float)line.sprite->getWidth()) ;
                    	
                    }

                    it_obst = obstaculos->find(-i);
                    if(it_obst != obstaculos->end()){
                    	line.sprite2 = it_obst->second;
                    	line.spriteX2 = -0.5 - 17*(float)SCREEN_WIDTH/(80*(float)line.sprite->getWidth()) ;
                    	
                    }

                    lines.push_back(line);
                }
                cout<<it->second<<endl;
                iter_anterior += iteraciones;
            }

            int N = lines.size();

            pos = 1;


			//While application is running
			while( !quit ) {


				while( SDL_PollEvent( &e ) != 0 ) {
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    this->keyEvent( e );
				}

                SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(this->renderer);

                int startPos = pos/segL;
				x=0;
				dx=0;

                backgroundMove();



                for(int n = startPos; n<startPos+101; n++) {
                    pos = autito.getPosition();
                    Line &l = lines[n];
                    l.project(x, 1300, pos);

                    x+=dx;
                    dx+=l.curve;


                    l.clip = maxy;
                    if (l.Y < 0 || l.Y>SCREEN_HEIGHT )
                        continue;
                    maxy = l.Y;


                    SDL_Color pasto = (n / 5) % 2 ? verde : verdeOscuro;
                    SDL_Color borde = (n / 2) % 2 ? rojo : blanco;
                    SDL_Color linea = (n / 3) % 2 ? gris : blanco;

                    Line p = lines[(n - 1)];


                    fondo->setearFigura(SCREEN_WIDTH/2, p.Y, SCREEN_WIDTH, SCREEN_WIDTH/2, l.Y, SCREEN_WIDTH, this->renderer, pasto);
                    clip->setearFigura(p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2,this->renderer,borde);
                    pista->setearFigura(p.X, p.Y,p.W, l.X, l.Y, l.W,this->renderer,gris);
                    line->setearFigura(p.X, p.Y, p.W*0.05,p.X, l.Y, l.W*0.05, this->renderer, linea);

                }


                 for(int n=startPos+101; n>startPos; n--)
      				 lines[n].drawSprite(this->renderer);
      				
                int curve =  lines[(pos/200)].curve;

                checkCurveAndSetCentrifuga(curve);
                autito.calculateMove(PressUP, curveR, curveL);
                car.render(autito.getX(), autito.getY(), this->renderer);

                SDL_RenderPresent(this->renderer);

			}

		}

	}

	//Free resources and close SDL
	close( &(this->renderer),&(this->window));
}

void ClienteController::keyEvent(SDL_Event e) {


    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:        autito.moveUP_KD(pos); PressUP = true; break;
            case SDLK_DOWN:      autito.moveDown_KD(pos); break;
            case SDLK_LEFT:      autito.moveLeft_KD();break;
            case SDLK_RIGHT:     autito.moveRight_KD(); break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        switch( e.key.keysym.sym ) {
			case SDLK_UP:       autito.moveUP_KU(pos); PressUP = false; break;
            case SDLK_DOWN:     autito.moveDown_KU(pos);  break;
            case SDLK_LEFT:     autito.moveLeft_KU(); break;
            case SDLK_RIGHT:    autito.moveRight_KU();  break;
        }
    }

}

bool ClienteController::loadMedia() {
    //Loading success flag
    bool success = true;

    //Load sprite sheet textura
    if( !sky.loadFromFile("img/sky.png", this->renderer) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    if( !trees.loadFromFile("img/trees.png", this->renderer) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    if( !hills.loadFromFile("img/hills.png", this->renderer) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }

    if( !car.loadFromFile("img/ferrari_straight1.png", this->renderer) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }

    arbol = new Textura();
        if( !arbol->loadFromFile("img/palmera.png", this->renderer) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }


    cartel = new Textura();
        if( !cartel->loadFromFile("img/cartel1.png", this->renderer) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }

    cartel2 = new Textura();
        if( !cartel2->loadFromFile("img/cartel2.png", this->renderer) )
    {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }


    //Open the font
	font = TTF_OpenFont( "fonts/box.otf", 28 );
	if( font == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

    




    return success;
}

void ClienteController::checkCurveAndSetCentrifuga(int curve) {
    if (curve < 0){ //curva a la derecha
        curveR = true;
        curveL = false;
    }
    if (curve > 0) { //curva a la izquierda
        curveL = true;
        curveR = false;
    }
    if(curve == 0){
        curveR = false;
        curveL = false;
    }
}

void ClienteController::backgroundMove() {
    if (curveR && autito.isMoving()) {
        sky.render(0, 0, this->renderer);
        hills.render(offsetBackgroundHills, 20, this->renderer);
        trees.render(offsetBackgroundTree, 20, this->renderer);
        offsetBackgroundHills -= 0.05;
        offsetBackgroundTree -= 0.1;
    }
    if (curveL && autito.isMoving()) {
        sky.render(0, 0, this->renderer);
        hills.render(offsetBackgroundHills, 20, this->renderer);
        trees.render(offsetBackgroundTree, 20, this->renderer);
        offsetBackgroundHills += 0.05;
        offsetBackgroundTree += 0.1;
    }
    else{
        sky.render(0, 0, this->renderer);
        hills.render(offsetBackgroundHills, 20, this->renderer);
        trees.render(offsetBackgroundTree, 20, this->renderer);
    }
}

void ClienteController::verMinimapa(){
    this->threadGraficoMinimapa.start();

}



bool ClienteController::getString(string* str,string optText){
	
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 0xFF };
		SDL_Event e;

		//The current input text.
		std::string inputText = "";

		ingreso->loadFromRenderedText( inputText.c_str(), textColor,font,renderer );


		opcion->loadFromRenderedText( optText.c_str(), textColor,font,renderer );

	//The rerender text flag
	bool renderText = false;
	bool quit = false;
	bool termino = false;

	while(!quit && !termino){
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			//Special key input
			else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
			{
				//Handle backspace
				if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
				{
					//lop off character
					inputText.pop_back();
					renderText = true;
				}

				if (e.key.keysym.sym == SDLK_RETURN){
					termino = true;
					*str = inputText;
				}
			}
			//Special text input event
			else if( e.type == SDL_TEXTINPUT )
			{

					//Append character
					inputText += e.text.text;
					renderText = true;
			}
		}

		//Rerender text if needed
		if( renderText )
		{
			//Text is not empty
			if( inputText != "" )
			{
				//Render new text
				ingreso->loadFromRenderedText( inputText.c_str(), textColor,font, renderer );
			}
			//Text is empty
			else
			{
				//Render space texture
				ingreso->loadFromRenderedText( " ", textColor,font,renderer );
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( renderer );

		//Render text textures
		opcion->render( ( SCREEN_WIDTH - opcion->getWidth() ) / 2, 0,renderer );
		ingreso->render( ( SCREEN_WIDTH - ingreso->getWidth() ) / 2, opcion->getHeight(),renderer );

		//Update screen
		SDL_RenderPresent( renderer );
	}

	SDL_FlushEvents(SDL_KEYDOWN,SDL_TEXTINPUT);
	return quit;
}






