//
// Created by florencia on 03/09/17.
//

#include <iomanip>
#include "../../headers/com.pepas.controllers/clienteController.h"
#include <zconf.h>
#include <vector>

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024

#define OFFSET 16
#define LINEAS 400


ClienteController::ClienteController(const char *archivo) {
    this->socketData = this->clienteParser->parsearXML(archivo);
    this->cliente = new Cliente();
    this->threadRecibir = recvThread(cliente);
    this->threadEnviar = aliveSignalThread(cliente);
    this->reconexion = false;
    strcpy(this->ipAddress, socketData.ip);
    cout << ipAddress << endl;
    cout << socketData.ip << endl;
    strcpy(this->testFile, socketData.rutafile);
    //this->threadGraficoMinimapa=threadMinimapa(cliente);

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int velX = Y;
    curveSet = 0;

    this->obstaculos = new map<int, Textura *>();
    this->ingreso = new Textura();
    this->opcion = new Textura();
    this->autito = new Auto();
    this->car = new Textura();

    PressUP = false;
    offsetBackgroundTree = -2000;
    offsetBackgroundHills = -2000;


}


ClienteController::ClienteController(ClienteParser *clientePaser) {
    this->clienteParser = clientePaser;

}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)


void ClienteController::conectar() {

    if (this->cliente->estaConectado()) {
        cout << "Usted ya esta conectado" << endl;
        return;
    }

    //Esto es para cerrar el thread de la conexion anterior.
    if (reconexion) {
        this->dejarRecibir();
        reconexion = false;
    }
    if (this->conectarConElServidor() == -1) {
        cout << "Ocurrio un error al intentar conectarse, intente nuevamente" << endl;
    } else {
        cout << "Haciendo cambio de puerto" << endl;
        this->obtengoPuertoNuevoYHagoConectar();
        //this->verMinimapa();


    }
}


int ClienteController::conectarConElServidor() {
    return this->cliente->conectarseAlServidor(this->ipAddress, socketData.puerto);
}


void ClienteController::desconectarseDelServidor() {
    if (!this->cliente->estaConectado()) {
        cout << "Usted no esta conectado" << endl;
        return;
    }
    if (cliente->estalogueado()) {
        this->logOut();
    }

    this->cliente->desconectarse();
    this->obtenerCliente()->obtenerSocket()->CerrarConexion(this->obtenerCliente()->obtenerSocketFD());
    //this->obtenerCliente()->obtenerSocket()->CerrarSocket(this->obtenerCliente()->obtenerSocketFD());
    reconexion = false;
    this->dejarRecibir();
    this->cliente->vaciarColaChat();
    this->cliente->vaciarColaBuzon();


    cout << "Se ha desconectado" << endl;

}


void ClienteController::logOut() {
    if (!cliente->estalogueado()) {
        cout << "Debe loguearse para desloguearse" << endl;
        return;
    }

    this->obtenerCliente()->desloguearse();
    string usuario = this->obtenerCliente()->obtenerUsuario()->getNombre();
    this->obtenerCliente()->enviarMensaje(this->obtenerCliente()->procesarMensaje(usuario));
    this->obtenerCliente()->vaciarColaChat();
    this->obtenerCliente()->vaciarColaBuzon();


}

void ClienteController::logIn(string usuario, string clave) {
    if (!this->cliente->estaConectado()) {
        cout << "Debe conectarse para loguearse" << endl;
        return;
    }

    if (cliente->estalogueado()) {
        cout << "Usted ya esta logueado" << endl;
        return;
    }

    this->cliente->logIn(usuario, clave);

    if (this->cliente->estalogueado()) {
        this->empezarRecibir();
    }

}


void ClienteController::stressTest() {
    if (!cliente->estalogueado()) {
        cout << "Debe loguearse para enviar un mensaje" << endl;
        return;
    }
    string milisegundos, totalmili;
    cout << "Ingrese cantidad de milisegundos entre mensajes: ";
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
        if (total % mili != 0) {
            valido = false;
            cout << "Datos ingresados invalidos, deben ser multiplo" << endl;
            loggear("Datos ingresados invalidos, deben ser multiplo", 1);
        }
    } catch (std::invalid_argument) {
        cout << "Ingrese unicamente un numero " << '\n';
    }

    ifstream myReadFile;
    myReadFile.open(testFile); //this->clienteParser->obtenerRutaTestFile()
    string stressMsg;
    if (myReadFile.is_open() && valido) {
        while (!myReadFile.eof()) {
            getline(myReadFile, stressMsg);
            myReadFile.ignore();
        }
    }
    myReadFile.close();

    int i = 0;
    if (valido) {
        do {
            usleep(mili);
            enviarBroadcast(stressMsg);
            i += mili;

        } while (i != total);
    }


}


void ClienteController::enviarMensajePrivado() {
    if (!cliente->estalogueado()) {
        cout << "Debe loguearse para enviar un mensaje" << endl;
        return;
    }
    string texto, mensajeProcesado, destinatario, bug;
    cout << this->obtenerCliente()->obtenerUsuario()->getNombre() << " ingresa el mensaje: ";
    //TODO aca hay un bug que no lo entiendo, si no pongo las variables de esta forma anda mal.
    getline(cin, bug);
    getline(cin, texto);
    cout << "Ingresa el ususario destino: ";
    cin >> destinatario;
    Mensaje *mensaje = new Mensaje(Mensaje::PRIVATE_MSG, texto, this->obtenerCliente()->obtenerUsuario()->getNombre(),
                                   destinatario);
    mensajeProcesado = this->obtenerCliente()->procesarMensaje(mensaje);
    this->obtenerCliente()->enviarMensaje(mensajeProcesado);


}

void ClienteController::salirDelPrograma() {
    cout << "SALISTE" << endl;

}

ClienteController::~ClienteController() {
    delete this->cliente;
}

Cliente *ClienteController::obtenerCliente() {
    return this->cliente;
}


void ClienteController::obtengoPuertoNuevoYHagoConectar() {
    /*Recibo 4 bytes en donde ya se que voy a recibir 4 bytes con el puerto nuevo*/
    string puerto = this->obtenerCliente()->obtenerSocket()->Recibir(this->obtenerCliente()->obtenerSocketFD(), 4);
    if (puerto == "0005") {
        cout << "El servidor ya esta ocupado con su maxima capacidad" << endl;
        return;
    }
    /*Cierro la conexion con el puerto del xml*/
    cout << "El puerto recibido es: " << puerto << endl;
    this->obtenerCliente()->obtenerSocket()->CerrarConexion(this->obtenerCliente()->obtenerSocketFD());

    /*Me conecto al nuevo servidor*/
    this->obtenerCliente()->conectarseAlServidor(this->ipAddress, stoi(puerto, nullptr, 10));
    cout << "Conectado satisfactorio con puerto: " << puerto << endl;
    this->cliente->conectarse();
    this->empezarRecibir();
    this->reconexion = true;

}

void ClienteController::empezarRecibir() {
    this->threadRecibir.start();
    this->threadEnviar.start();
}

void ClienteController::dejarRecibir() {
    this->threadEnviar.join();
    this->threadRecibir.join();

}


int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}


void ClienteController::entrarAlChat() {
    if (!cliente->estalogueado()) {
        cout << "Debe loguearse para enviar un mensaje" << endl;
        return;
    }

    //system("clear");
    cout << "Presione & para salir del chat" << endl;
    string entrada("");
    cin.ignore();

    do {

        while (!this->obtenerCliente()->obtenerColaChat().empty()) {
            if (kbhit()) {
                break;
            }
            cout << this->obtenerCliente()->obtenerColaChat().front() << flush << endl;
            this->obtenerCliente()->desencolarColaChat();
        }

        if (kbhit()) {
            getline(cin, entrada);
            cout << "\e[A";
            if (entrada.compare("&\0") == 0)
                break;
            enviarBroadcast(entrada);
        }
    } while (cliente->estalogueado());
}


void ClienteController::verBuzon() {
    if (!cliente->estalogueado()) {
        cout << "Debe loguearse para ver el buzon" << endl;
        return;
    }

    this->obtenerCliente()->verBuzon();
}


void ClienteController::enviarBroadcast(string entrada) {

    if (!cliente->estalogueado()) {
        cout << "Debe loguearse para enviar un mensaje" << endl;
        return;
    }
    string mensajeProcesado;
    string destinatario = "";
    Mensaje *mensaje = new Mensaje(Mensaje::BROADCAST_MSG, entrada,
                                   this->obtenerCliente()->obtenerUsuario()->getNombre(), destinatario);
    mensajeProcesado = this->obtenerCliente()->procesarMensaje(mensaje);
    this->obtenerCliente()->enviarMensaje(mensajeProcesado);
}


void ClienteController::dibujar() {

    if (!init(SCREEN_WIDTH, SCREEN_HEIGHT, &(this->window), &(this->renderer))) {
        printf("Failed to initialize!\n");
    } else {
        //Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            //Main loop flag
            bool quit = false;
            clock_t startTime;

            //Event handler
            SDL_Event e;


            string usuario;
            string password;



            //Enable text input
            SDL_StartTextInput();

            do {
                if (!this->cliente->estaConectado())
                    this->conectar();


                quit = getString(&usuario, "Usuario :");

                if (!quit)
                    quit = getString(&password, "Clave :");

                if (!quit)
                    this->logIn(usuario, password);
                sleep(1);

            } while (!this->cliente->estalogueado() && !quit);

            while (!this->cliente->recibioFinDeMapa() && !quit) {
                cout << "Esperando jugadores" << endl;
                sleep(3);
            }

            this->carAsign();
            Mix_PlayMusic( soundTrack, -1 );
            Mix_VolumeMusic(10);
            Mix_Volume(-1, 10);

            //Disable text input
            SDL_StopTextInput();


            SDL_Color gris = {0xA3, 0xA3, 0xA3, 0xFF};
            SDL_Color grisOscuro = {0xA0, 0xA0, 0xA0, 0xFF};
            SDL_Color verde = {0x00, 0xCC, 0x00, 0xFF};
            SDL_Color verdeOscuro = {0x00, 0x99, 0x00, 0xFF};
            SDL_Color blanco = {0xFF, 0xFF, 0xFF, 0xFF};
            SDL_Color rojo = {0xFF, 0x00, 0x00, 0xFF};
            SDL_Color transparente = {0x00, 0x00, 0x00, 0x00};

            Figura *pista = new Figura();
            Figura *fondo = new Figura();
            Figura *line = new Figura();
            Figura *clip = new Figura();

            int maxy = SCREEN_HEIGHT;

            roadW = 2000;
            segL = 50; //segment length
            camD = 0.84f; //camera depth

            x = 0;
            y = 0;
            z = 0;

            struct Line {
                double x, y, z; //3d center of line
                double X, Y, W; //screen coord
                double scale;
                double camD = 0.5;
                double roadW = 2000;
                double curve, spriteX, clip, spriteX2, spriteXR1, spriteXR2, spriteXR3;
                Textura *sprite;
                Textura *sprite2;
                Textura *spriteR1;
                Textura *spriteR2;
                Textura *spriteR3;

                Line() {
                    spriteX = spriteX2 = x = y = z = 0;
                    sprite = NULL;
                    sprite2 = NULL;
                    spriteR1 = NULL;
                    spriteR2 = NULL;
                    spriteR3 = NULL;
                    spriteXR1 = 0;
                    spriteXR2 = 0;
                    spriteXR3 = 0;
                }

                void project(int camX, int camY, int camZ) {
                    scale = camD / (z - camZ);
                    X = (1 + scale * (x - camX)) * SCREEN_WIDTH / 2;
                    Y = ((1 - scale * (y - camY)) * SCREEN_HEIGHT / 2);
                    W = scale * (roadW) * SCREEN_WIDTH / 2;

                }

                void drawSprite(SDL_Renderer *renderer) {
                    if (spriteX != 0) {
                        int w = sprite->getWidth();
                        int h = sprite->getHeight();

                        double destX = X + scale * spriteX * SCREEN_WIDTH / 2;//* SCREEN_WIDTH/2
                        double destY = Y + 4;
                        double destW = w * W / 266;
                        double destH = h * W / 266;

                        destX += destW * spriteX; //offsetX
                        destY += destH * (-1);    //offsetY

                        SDL_RenderSetScale(renderer, destW / w, destH / h);
                        sprite->render(destX / destW * w, destY * h / destH, renderer);
                        SDL_RenderSetScale(renderer, 1, 1);
                    }

                    if (spriteX2 != 0) {
                        int w = sprite2->getWidth();
                        int h = sprite2->getHeight();

                        double destX = X + scale * spriteX2 * SCREEN_WIDTH / 2;
                        double destY = Y + 4;
                        double destW = w * W / 266;
                        double destH = h * W / 266;

                        destX += destW * spriteX2; //offsetX
                        destY += destH * (-1);    //offsetY


                        SDL_RenderSetScale(renderer, destW / w, destH / h);
                        sprite2->render(destX / destW * w, destY * h / destH, renderer);
                        SDL_RenderSetScale(renderer, 1, 1);
                    }
                    if (spriteXR1 != 0) {
                        int w = spriteR1->getWidth();
                        int h = spriteR1->getHeight();

                        double destX = X + scale * spriteXR1 * SCREEN_WIDTH / 2;
                        double destY = Y + 4;
                        double destW = w * W / 700;
                        double destH = h * W / 700;

                        destX += destW * spriteXR1;
                        destY += destH * (-1);


                        SDL_RenderSetScale(renderer, destW / w, destH / h);
                        spriteR1->render(destX / destW * w, destY * h / destH, renderer);
                        SDL_RenderSetScale(renderer, 1, 1);
                    }
                    if (spriteXR2 != 0) {
                        int w = spriteR2->getWidth();
                        int h = spriteR2->getHeight();

                        double destX = X + scale * spriteXR2 * SCREEN_WIDTH / 2;
                        double destY = Y + 4;
                        double destW = w * W / 700;
                        double destH = h * W / 700;

                        destX += destW * spriteXR2; //offsetX
                        destY += destH * (-1);    //offsetY


                        SDL_RenderSetScale(renderer, destW / w, destH / h);
                        spriteR2->render(destX / destW * w, destY * h / destH, renderer);
                        SDL_RenderSetScale(renderer, 1, 1);
                    }
                    if (spriteXR3 != 0) {
                        int w = spriteR3->getWidth();
                        int h = spriteR3->getHeight();

                        double destX = X + scale * spriteXR3 * SCREEN_WIDTH / 2;
                        double destY = Y + 4;
                        double destW = w * W / 730;
                        double destH = h * W / 730;

                        destX += destW * spriteXR3;
                        destY += destH * (-1);

                        SDL_RenderSetScale(renderer, destW / w, destH / h);
                        spriteR3->render(destX / destW * w, destY * h / destH, renderer);
                        SDL_RenderSetScale(renderer, 1, 1);
                    }
                }
            };

            std::vector<Line> lines;

            //list<pair<int, double>> Track; /*distancia , curvatura*/

            for (auto it = this->cliente->obtenerMapa()->obtenerObjetos()->begin();
                 it != this->cliente->obtenerMapa()->obtenerObjetos()->end(); ++it) {
                Objeto *obj = *it;
                int distancia = obj->getDistancia() * 4;
                int arbol = obj->getArbol();
                int cartel = obj->getCartel();
                string lado = obj->getLado();
                if (arbol != 0 && lado == "D")
                    obstaculos->emplace(distancia, this->arbol);
                if (arbol != 0 && lado == "I")
                    obstaculos->emplace(-distancia, this->arbol);
                if (cartel == 80 && lado == "D")
                    obstaculos->emplace(distancia, this->cartel);
                if (cartel == 80 && lado == "I")
                    obstaculos->emplace(-distancia, this->cartel);
                if (cartel == 120 && lado == "D")
                    obstaculos->emplace(distancia, this->cartel2);
                if (cartel == 120 && lado == "I")
                    obstaculos->emplace(-distancia, this->cartel2);

            }
            std::map<int, Textura *>::iterator it_obst;

            list<pair<int, float>> Track = this->cliente->obtenerTrack(); //TODO anda igual

    /*         obstaculos->emplace(50,cartel);
             obstaculos->emplace(-50,cartel);
             obstaculos->emplace(50,cartel);
             obstaculos->emplace(-75,cartel2);
             obstaculos->emplace(75,cartel2);
             obstaculos->emplace(300,arbol);
             obstaculos->emplace(-100,arbol);
             obstaculos->emplace(100,arbol);
*/
            // Track.emplace_back(5000,0);
            /*Armo la pista*/
            int iter_anterior = 0;
            for (auto it = Track.begin(); it != Track.end(); it++) {
                int iteraciones = it->first;
                //cout<<"Tramo:"<<iteraciones<<endl;
                for (int i = iter_anterior; i < iteraciones + iter_anterior; i++) {
                    Line line;
                    line.z = i * segL;
                    line.curve = it->second / 4;
                    it_obst = obstaculos->find(i);
                    if (it_obst != obstaculos->end()) {
                        line.sprite = it_obst->second;
                        line.spriteX = -0.375 + (double) SCREEN_WIDTH / (5 * (double) line.sprite->getWidth());

                    }
                    it_obst = obstaculos->find(-i);
                    if (it_obst != obstaculos->end()) {
                        line.sprite2 = it_obst->second;
                        line.spriteX2 = -0.5 - 17 * (double) SCREEN_WIDTH / (80 * (double) line.sprite2->getWidth());
                    }
                    lines.push_back(line);
                }

                iter_anterior += iteraciones;
            }

            int N = lines.size();
            pos = 1;
            int contador = 0;
            double noDraw = 0;
            double noDraw2 = 0;
            double noDraw3 = 0;


            //Start timer
			startTime = clock();
            //While application is running
            while (!quit) {


                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    this->keyEvent(e);
                }

                SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(this->renderer);

                int startPos = pos / segL;
                x = 0;
                dx = 0;

                backgroundMove();

                //TODO aca tiene que recibir la tecla que toco;

                for (int n = startPos; n < startPos + LINEAS + 1; n++) {
                    pos = cliente->getPosition();
                    Line &l = lines[n];
                    l.project(x, 1300, pos);
                    x += dx;
                    dx += l.curve;

                    l.clip = maxy;
                    if (l.Y < 0 || l.Y > SCREEN_HEIGHT)
                        continue;
                    maxy = l.Y;

                    SDL_Color pasto = (n / 20) % 2 ? verde : verdeOscuro;
                    SDL_Color borde = (n / 8) % 2 ? rojo : blanco;
                    SDL_Color linea = (n / 12) % 2 ? gris : blanco;

                    Line p = lines[(n - 1)];

                    fondo->setearFigura(SCREEN_WIDTH / 2, p.Y, SCREEN_WIDTH, SCREEN_WIDTH / 2, l.Y, SCREEN_WIDTH,
                                        this->renderer, pasto);
                    clip->setearFigura(p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2, this->renderer, borde);
                    pista->setearFigura(p.X, p.Y, p.W, l.X, l.Y, l.W, this->renderer, gris);
                    line->setearFigura(p.X, p.Y, p.W * 0.05, p.X, l.Y, l.W * 0.05, this->renderer, linea);

                }


                /*  if (!this->cliente->obtenerRivalList().empty()) {
                      for (list<Rival *>::iterator it = this->cliente->obtenerRivalList().begin(); it != this->cliente->obtenerRivalList().end(); ++it) {
                          Rival *rival = *it;
                          if (rival->getDibujar()) {
                              lines[startPos + rival->getHorizonte() +4].spriteP2 = this->getTextura(rival->getPlayer());
                              lines[startPos + rival->getHorizonte() +4].spriteXP2 = 0.0056 * rival->getPosX() - 2.8;
                              rival->notDibujar();
                          }
                          break;
                      }
                  }*/


                int i = 0;
                list<Rival *>::iterator it = this->cliente->obtenerRivalList().begin();
                while (i < this->cliente->obtenerRivalList().size()){

                    i++;
                    Rival *rival = *it;
         /*           if (rival->getDibujar()) {
                        dibujarRival(lines[startPos + rival->getHorizonte() + OFFSET].X,
                                     lines[startPos + rival->getHorizonte() + OFFSET].Y,
                                     lines[startPos + rival->getHorizonte() + OFFSET].W,
                                     lines[startPos + rival->getHorizonte() + OFFSET].scale,
                                     0.0056 * rival->getPosX() - 2.8,
                                     this->getTextura(rival->getPlayer()));
                    }
                    rival->notDibujar();*/

                    if(rival->getDibujar()){

                        if (i==1){

                            lines[startPos + rival->getHorizonte() + OFFSET].spriteR1 = this->getTextura(
                                    rival->getPlayer());
                            lines[startPos + rival->getHorizonte() + OFFSET].spriteXR1 = 0.0056 * rival->getPosX() - 2.8;
                            if (noDraw != startPos + rival->getHorizonte() + OFFSET) {
                                lines[noDraw].spriteXR1 = 0;
                                //lines[startPos + rival->getHorizonte() + OFFSET].drawSprite(renderer);
                                noDraw = startPos + rival->getHorizonte() + OFFSET;

                            }
                        }else if(i==2){

                            lines[startPos + rival->getHorizonte() + OFFSET].spriteR2 = this->getTextura(
                                    rival->getPlayer());
                            lines[startPos + rival->getHorizonte() + OFFSET].spriteXR2 = 0.0056 * rival->getPosX() - 2.8;
                            if (noDraw2 != startPos + rival->getHorizonte() + OFFSET) {
                                lines[noDraw2].spriteXR2 = 0;
                                //lines[startPos + rival->getHorizonte() + OFFSET].drawSprite(renderer);
                                noDraw2 = startPos + rival->getHorizonte() + OFFSET;
                            }
                        }else{
                            lines[startPos + rival->getHorizonte() + OFFSET].spriteR3 = this->getTextura(
                                    rival->getPlayer());
                            lines[startPos + rival->getHorizonte() + OFFSET].spriteXR3 = 0.0056 * rival->getPosX() - 2.8;
                            if (noDraw3 != startPos + rival->getHorizonte() + OFFSET) {
                                lines[noDraw3].spriteXR3 = 0;
                                //lines[startPos + rival->getHorizonte() + OFFSET].drawSprite(renderer);
                                noDraw3 = startPos + rival->getHorizonte() + OFFSET;
                            }
                            //puts("entre3");
                        }
                        rival->notDibujar();
                    }

                    std::list<Rival *>::iterator it2 = std::next(it, 1);
                   // printf("ciclo\n");
                }
               // printf("sali\n");




            /*    switch (this->cliente->obtenerCantidadDePlayersADibujar()) {
                    case 1: {
                        list<Rival *>::iterator it = this->cliente->obtenerRivalList().begin();
                        Rival *rival = *it;
                        if (rival->getDibujar()) {
                            lines[startPos + rival->getHorizonte() + OFFSET].spriteR1 = this->getTextura(
                                    rival->getPlayer());
                            lines[startPos + rival->getHorizonte() + OFFSET].spriteXR1 = 0.0056 * rival->getPosX() - 2.8;
                            if (noDraw != startPos + rival->getHorizonte() + OFFSET) {
                                lines[noDraw].spriteXR1 = 0;
                                //lines[startPos + rival->getHorizonte() + OFFSET].drawSprite(renderer);
                                noDraw = startPos + rival->getHorizonte() + OFFSET;
                            }
                            rival->notDibujar();
                        }
                    }
                        break;
                    case 2: {
                        list<Rival *>::iterator it = this->cliente->obtenerRivalList().begin();
                        Rival *rival = *it;
                        if (rival->getDibujar()) {
                            lines[startPos + rival->getHorizonte() + OFFSET].spriteR1 = this->getTextura(rival->getPlayer());
                            lines[startPos + rival->getHorizonte() + OFFSET].spriteXR1 = 0.0056 * rival->getPosX() - 2.8;
                            noDraw = startPos + rival->getHorizonte() + OFFSET;
                            rival->notDibujar();
                        }
                        std::list<Rival *>::iterator it2 = std::next(this->cliente->obtenerRivalList().begin(), 1);
                        Rival *rival2 = *it2;
                        if (rival2->getDibujar()) {
                            lines[startPos + rival2->getHorizonte() + OFFSET].spriteR2 = this->getTextura(rival2->getPlayer());
                            lines[startPos + rival2->getHorizonte() + OFFSET].spriteXR2 = 0.0056 * rival2->getPosX() - 2.8;
                            noDraw2 = startPos + rival->getHorizonte() + OFFSET;
                            rival2->notDibujar();
                        }

                    }
                        break;
                }*/
                for (int n = startPos + LINEAS; n > startPos; n--) {
                    lines[n].drawSprite(this->renderer);
                }
                //arregla el problema del noDraw
                for (int j = startPos + LINEAS - 1; j < startPos + LINEAS + 5; j++) {
                    lines[j].spriteXR1 = 0;
                    lines[j].spriteXR2 = 0;
                    lines[j].spriteXR3 = 0;
                }

                /*  int posP2x = 230;
                  lines[startPos+posP2y].spriteP2 = player3;
                  lines[posP2y].spriteXP2 = 0.0059 * posP2x - 3;
                  lines[startPos+posP2y].drawSprite(this->renderer);*/

                curveSet = lines[(pos / segL)].curve;

                cout<<pos/200<<endl;


                checkCurveAndSetCentrifuga(curveSet);
                //autito->calculateMove(PressUP, curveR, curveL); //TODO lo hace el servidor

                car->render(cliente->getX(), 618, this->renderer);
                this->actualizarMinimapa(this->cliente->getMinimapa());
                this->renderVelocidad();
                this->renderTiempo(startTime);



                posMoving = cliente->getPosition();

                //////

                this->renderDistancia(posMoving);

                SDL_RenderPresent(this->renderer);


                //////////
                if (posMoving != pos) {
                    moving = true;
                    //Mix_PlayChannel(-1,gUp,0);
                } else
                	moving = false;
                   // Mix_HaltChannel(-1);
            }

        }

    }

    //Free resources and close SDL
    close(&(this->renderer), &(this->window));
    //this->desconectarseDelServidor();
}


bool ClienteController::loadMedia() {
    //Loading success flag
    bool success = true;

    //Load sprite sheet textura
    if (!sky.loadFromFile("img/sky.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    if (!trees.loadFromFile("img/trees.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    if (!hills.loadFromFile("img/hills.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }

    arbol = new Textura();
    if (!arbol->loadFromFile("img/palmera.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }


    cartel = new Textura();
    if (!cartel->loadFromFile("img/cartel1.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }

    cartel2 = new Textura();
    if (!cartel2->loadFromFile("img/cartel2.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    player1 = new Textura();
    if (!player1->loadFromFile("img/ferrari1.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    player2 = new Textura();
    if (!player2->loadFromFile("img/ferrari2.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }

    player3 = new Textura();
    if (!player3->loadFromFile("img/ferrari3.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    player4 = new Textura();
    if (!player4->loadFromFile("img/ferrari4.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    player5 = new Textura();
    if (!player5->loadFromFile("img/ferrariGris.png", this->renderer)) {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }

    //Open the font
    login = TTF_OpenFont("fonts/box.otf", 28);
    if (login == NULL) {
        printf("Failed to load login font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    speed = TTF_OpenFont("fonts/velocidad.ttf", 28);
    if (speed == NULL) {
        printf("Failed to load speed font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    tiempo = TTF_OpenFont("fonts/time.TTF", 28);
    if (tiempo == NULL) {
        printf("Failed to load time font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    score = TTF_OpenFont("fonts/score.ttf", 28);
    if (score == NULL) {
        printf("Failed to load score font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    gUp = Mix_LoadWAV( "audios/up.wav" );
    if( gUp == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gLeft = Mix_LoadWAV( "audios/left.wav" );
    if( gLeft == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gRight = Mix_LoadWAV( "audios/right.wav" );
    if( gRight == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gLeave = Mix_LoadWAV( "audios/soltar.wav" );
    if( gLeave == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gBreak = Mix_LoadWAV( "audios/freno.wav" );
    if( gBreak == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    soundTrack = Mix_LoadMUS( "audios/musicafondo.mp3" );
    if( soundTrack == NULL )
    {
        printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }



    return success;
}

void ClienteController::checkCurveAndSetCentrifuga(double curve) {
    if (curve < 0) { //curva a la derecha
        curveR = true;
        curveL = false;
    }
    if (curve > 0) { //curva a la izquierda
        curveL = true;
        curveR = false;
    }
    if (curve == 0) {
        curveR = false;
        curveL = false;
    }
}

void ClienteController::backgroundMove() {
    if (curveR && moving) {
        sky.render(0, 0, this->renderer);
        hills.render(offsetBackgroundHills, 20, this->renderer);
        trees.render(offsetBackgroundTree, 20, this->renderer);
        offsetBackgroundHills -= 0.5;
        offsetBackgroundTree -= 1;
    }
    if (curveL && moving) {
        sky.render(0, 0, this->renderer);
        hills.render(offsetBackgroundHills, 20, this->renderer);
        trees.render(offsetBackgroundTree, 20, this->renderer);
        offsetBackgroundHills += 0.5;
        offsetBackgroundTree += 1;
    } else {
        sky.render(0, 0, this->renderer);
        hills.render(offsetBackgroundHills, 20, this->renderer);
        trees.render(offsetBackgroundTree, 20, this->renderer);
    }
}

void ClienteController::verMinimapa() {
    this->threadGraficoMinimapa.start();

}

void ClienteController::renderVelocidad(){
    string vel = "Velocidad: " + to_string(this->cliente->getVelocidad());

    SDL_Color textColor = {0, 0, 0, 0xFF};

    opcion->loadFromRenderedText(vel.c_str(),textColor,speed,renderer);
    opcion->render((SCREEN_WIDTH - opcion->getWidth())*3 / 4, 0, renderer);

}

void ClienteController::renderTiempo(clock_t startTime) {
	int secondsPassed;
	int minutesPassed;
	secondsPassed =  (clock() - startTime) / CLOCKS_PER_SEC;
    minutesPassed = secondsPassed / 60;

    secondsPassed = secondsPassed - (minutesPassed * 60);

	string tiempo = "Tiempo: " + to_string((int)minutesPassed) + ":" + to_string((int)secondsPassed);
	int copiaMinutos=minutesPassed;

	SDL_Color textColor = {0, 0, 0, 0xFF};


	opcion->loadFromRenderedText(tiempo.c_str(),textColor,speed,renderer);
	opcion->render(((SCREEN_WIDTH - opcion->getWidth()) * 3 / 4 ), 30, renderer);
}



void ClienteController::renderDistancia(int distancia) {
    int dist=distancia/200;

    string distance = "Distancia: " + to_string(dist) + " m.";
    SDL_Color textColor = {0, 0, 0, 0xFF};

    opcion->loadFromRenderedText(distance.c_str(),textColor,speed,renderer);
    opcion->render(((SCREEN_WIDTH - opcion->getWidth()) * 3 / 4 ), 60, renderer);

}



bool ClienteController::getString(string *str, string optText) {

    //Set text color as black
    SDL_Color textColor = {0, 0, 0, 0xFF};
    SDL_Event e;

    //The current input text.
    std::string inputText = "";


    ingreso->loadFromRenderedText(inputText.c_str(), textColor, login, renderer);
    opcion->loadFromRenderedText(optText.c_str(), textColor, login, renderer);

    //The rerender text flag
    bool renderText = false;
    bool quit = false;
    bool termino = false;

    while (!quit && !termino) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
                //Special key input
            else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                //Handle backspace
                if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                    //lop off character
                    inputText.pop_back();
                    renderText = true;
                }

                if (e.key.keysym.sym == SDLK_RETURN) {
                    termino = true;
                    *str = inputText;
                }
            }
                //Special text input event
            else if (e.type == SDL_TEXTINPUT) {

                //Append character
                inputText += e.text.text;
                renderText = true;
            }
        }

        //Rerender text if needed
        if (renderText) {
            //Text is not empty
            if (inputText != "") {
                //Render new text
                ingreso->loadFromRenderedText(inputText.c_str(), textColor, login, renderer);
            }
                //Text is empty
            else {
                //Render space texture
                ingreso->loadFromRenderedText(" ", textColor, login, renderer);
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        //Render text textures
        opcion->render((SCREEN_WIDTH - opcion->getWidth()) / 2, 0, renderer);
        ingreso->render((SCREEN_WIDTH - ingreso->getWidth()) / 2, opcion->getHeight(), renderer);

        //Update screen
        SDL_RenderPresent(renderer);
    }

    SDL_FlushEvents(SDL_KEYDOWN, SDL_TEXTINPUT);
    return quit;
}


/*length/13/posy/posx*/
void ClienteController::procesarMensajePosicion(int pos, int x) {
    string stringACrear, stringProcesado;
    string separador = "/";
    string posy = to_string(pos);
    string posx = to_string(x);
    string id = this->cliente->obtenerUsuario()->getNombre();
    stringACrear = separador + "13" + separador + id + separador + posy + separador + posx;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);
}

string ClienteController::agregarPadding(int lenght) {
    string mensajeProcesado;
    string largo = to_string(lenght);
    if (lenght < 10)
        mensajeProcesado = "000" + largo;
    else if (lenght < 100)
        mensajeProcesado = "00" + largo;
    else if (lenght < 1000)
        mensajeProcesado = "0" + largo;
    else mensajeProcesado = largo;
    return mensajeProcesado;
}

void ClienteController::keyEvent(SDL_Event e) {


    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                Mix_PlayChannel( 0, gUp, -1 );
                enviarMoveUp();
                break;
            case SDLK_DOWN:
                Mix_PlayChannel( 3, gBreak, -1 );
                enviarMoveDown();
                break;
            case SDLK_LEFT:
                Mix_PlayChannel( 1, gRight, -1);
                enviarMoveLeft();
                break;
            case SDLK_RIGHT:
                Mix_PlayChannel( 2, gRight, -1 );
                enviarMoveRight();
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                Mix_HaltChannel(2);
                enviarNotMoveRight();
                break;
            case SDLK_UP:
                Mix_HaltChannel(0);
                enviarNotMoveUp();
                break;
            case SDLK_DOWN:
                Mix_HaltChannel(3);
                enviarNotMoveDown();
                break;
            case SDLK_LEFT:
                Mix_HaltChannel(1);
                enviarNotMoveLeft();
                break;
        }
    }

}

/*   padding/cod/ID/posY/tecla     */
void ClienteController::enviarMoveUp() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string posy = to_string(pos);
    string nombreUsuario = this->cliente->obtenerUsuario()->getNombre();
    string curva = to_string(curveSet);
    stringACrear = separador + "20" + separador + nombreUsuario + separador + posy + separador + curva;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);
}

void ClienteController::enviarMoveLeft() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string nombreUsuario = this->cliente->obtenerUsuario()->getNombre();
    string curva = to_string(curveSet);
    stringACrear = separador + "21" + separador + nombreUsuario + separador + curva;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);
}

void ClienteController::enviarMoveRight() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string nombreUsuario = this->cliente->obtenerUsuario()->getNombre();
    string curva = to_string(curveSet);
    stringACrear = separador + "22" + separador + nombreUsuario + separador + curva;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);
}

void ClienteController::enviarMoveDown() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string posy = to_string(pos);
    string nombreUsuario = this->cliente->obtenerUsuario()->getNombre();
    string curva = to_string(curveSet);
    stringACrear = separador + "23" + separador + nombreUsuario + separador + posy + separador + curva;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);
}

void ClienteController::enviarNotMoveUp() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string posy = to_string(pos);
    string nombreUsuario = this->cliente->obtenerUsuario()->getNombre();
    string curva = to_string(curveSet);
    stringACrear = separador + "24" + separador + nombreUsuario + separador + posy + separador + curva;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);
}

void ClienteController::enviarNotMoveLeft() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string nombreUsuario = this->cliente->obtenerUsuario()->getNombre();
    string curva = to_string(curveSet);
    stringACrear = separador + "25" + separador + nombreUsuario + separador + curva;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);

}

void ClienteController::enviarNotMoveRight() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string nombreUsuario = this->cliente->obtenerUsuario()->getNombre();
    string curva = to_string(curveSet);
    stringACrear = separador + "26" + separador + nombreUsuario + separador + curva;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);

}


void ClienteController::enviarNotMoveDown() {
    string stringACrear, stringProcesado;
    string separador = "/";
    string posy = to_string(pos);
    string nombreUsuario = this->cliente->obtenerUsuario()->getNombre();
    string curva = to_string(curveSet);
    stringACrear = separador + "27" + separador + nombreUsuario + separador + posy + separador + curva;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    this->cliente->enviarMensaje(stringProcesado);
}


void ClienteController::actualizarMinimapa(Minimapa *minimapa) {

    Recorredor *recorredor = new Recorredor();
    ///////////////////
    list<Segmento *> *ruta = minimapa->getRuta();
    for (list<Segmento *>::iterator it = ruta->begin(); it != ruta->end(); ++it) {
        Segmento *segm = *it;
        int X1 = (segm->getPosicionInicial()->getX());
        int Y1 = (segm->getPosicionInicial()->getY());
        int Y2 = (segm->getPosicionFinal()->getY());
        int X2 = (segm->getPosicionFinal()->getX());

        ///Pinto pista
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, X1, Y1, X2, Y2);
    }
    list<Objeto *> *objetos = minimapa->getObjetos();
    for (list<Segmento *>::iterator it = ruta->begin(); it != ruta->end(); ++it) {
        Segmento *segm = *it;
        recorredor->recorrer(segm, objetos);

    }
    list<Posicion *> *posicionesDeLosObjetos = recorredor->getPosicionesDeLosObjetos();
    for (list<Posicion *>::iterator it = posicionesDeLosObjetos->begin(); it != posicionesDeLosObjetos->end(); ++it) {
        Posicion *pos = *it;
        int x = (pos->getX());
        int y = (pos->getY());
        ///Pinto objeto
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawPoint(renderer, x, y);
    }
    map<int,Posicion*>* radar = minimapa->getRadar();
    for(map<int,Posicion*>::iterator it = radar->begin(); it!=radar->end();++it){
        Posicion* pos = it->second;
        int x = (pos->getX());
        int y = (pos->getY());
        ///Pinto auto en minimapa
        SDL_SetRenderDrawColor( renderer, 0xEE, 0x31, 0x37, 0xFF );
        SDL_RenderDrawPoint(renderer,x,y);
    }

    delete recorredor;

}

void ClienteController::carAsign() {

    switch (this->cliente->obtenerModel()) {
        case 1: {
            car = player1;
        }
            break;
        case 2: {
            car = player2;
        }
            break;
        case 3: {
            car = player3;
        }
            break;
        case 4: {
            car = player4;
        }
            break;
    }

}

Textura *ClienteController::getTextura(int player) {
    if (player == 1) {
        return player1;
    }
    if (player == 2) {
        return player2;
    }
    if (player == 3) {
        return player3;
    }
    if (player == 4) {
        return player4;
    }
    if (player == 5) {
        return player5;
    }
}

void ClienteController::dibujarRival(double X, double Y, double W, double scale, double spriteX, Textura *sprite) {

    int w = sprite->getWidth();
    int h = sprite->getHeight();

    double destX = X + scale * spriteX * SCREEN_WIDTH / 2;
    double destY = Y + 4;
    double destW = w * W / 700;
    double destH = h * W / 700;

    destX += destW * spriteX; //offsetX
    destY += destH * (-1);    //offsetY


    SDL_RenderSetScale(renderer, destW / w, destH / h);
    sprite->render(destX / destW * w, destY * h / destH, renderer);
    SDL_RenderSetScale(renderer, 1, 1);
}

