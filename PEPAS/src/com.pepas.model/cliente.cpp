#include "../../headers/com.pepas.model/cliente.h"
#include "../../headers/com.pepas.logger/Logger.h"



#define LOGIN 4
#define BROADCAST 2
#define BUZON 3
#define SERVIDOR 4
#define ERROR 5
#define SIGNAL_CONNECT 7
#define RUTAMINIMAPA 8
#define OBJETOSMINIMAPA 9
#define FINMAPAS 10
#define RUTAMAPA 11
#define OBJETOSMAPA 12
#define INFINITO 2147483647
#define AUTO_MOVE 20
#define CAMBIO_DE_PISTA 30
#define CONTEO 50
#define GO 40
#define STOP 69

Cliente::Cliente() {
    this->socketCliente = new Socket();
    this->usuario = new Usuario();
    this->socketFD=0;
    this->aliveCounter=0;
    this->logueado = false;
    this->minimapaCompleto=false;
    this->conectado = false;
    this->minimapa=new Minimapa();
    this->mapa = new Mapa();
    this->vista=new Vista();
    this->velocidad = 0;
    this->tiempo = "";
    posX =  1024/2 -100;
    posY = 768 - 1;
    finDeMapa = false;
    this->mapaCompleto = false;
    mover =false;
    this->scoresUsuarios = new list<pair<string,scores>>();
  
}
bool Cliente::minimapaEstaCompleto(){
    return (this->minimapaCompleto);
}
bool Cliente::mapaEstaCompleto(){
	return this->mapaCompleto;
}
/////////////////MINIMAPA///////////////////////////////////
void Cliente::actualizarRutaMiniMapa(int x1, int y1, int x2,int y2){
    Posicion* pos1=new Posicion(x1,y1);
    Posicion* pos2=new Posicion(x2,y2);
    Segmento* segmento= new Segmento(pos1,pos2);
    this->minimapa->agregarSegmento(segmento);
}

void Cliente::actualizarObjetosMiniMapa(int arbol,int cartel,int distancia,string lado){
	Objeto* objeto = new Objeto();
	objeto->setArbol(arbol);
	objeto->setCartel(cartel);
	objeto->setDistancia(distancia);
	objeto->setLado(lado);
	this->minimapa->agregarObjetos(objeto);
}
   //////////////////////////////////////////////////////////

void Cliente::graficarMinimapa(){
	if(!vista->minimapaGraficado()){
		vista->graficarMinimapa(this->minimapa);
	}
}




std::string obtenerParametros(std::string mensaje, int* i){
	std::string aux = "";
	*i = *i + 1;
	while(mensaje[*i] != '/' && mensaje[*i] != '\0'){
		aux = aux + mensaje[*i];
		*i = *i + 1;
	}

	return aux;

}

void Cliente::logIn(string usuario,string clave){
    if(this->logueado){
        cout << "Usted ya esta logueado" << endl;
        return;
    }

    this->obtenerUsuario()->setearNombre(usuario);
    this->obtenerUsuario()->setearContrasenia(clave);
    this->validarUsuario(obtenerUsuario());
    //this->parsearMensaje(this->recibirMensaje());

}

int Cliente::conectarseAlServidor(const char *ip, int puerto) {
    this->socketFD = this->socketCliente->Crear();
    cout<<"Socket creado... Conectando..."<<endl;
    cout<<"puerto "<<puerto<<"ip "<<ip<<endl;
    return this->obtenerSocket()->Conectar(this->socketFD,puerto, ip);

}


void Cliente::desconectarseDelServidor() {
    //neesito ver lo del servidor?
}


Cliente::~Cliente() {

}

void Cliente::asignarSocketFd(int socket) {
    this->socketFD=socket;

}

int Cliente::obtenerSocketFD() {
    return socketFD;
}

Socket* Cliente::obtenerSocket() {
        return this->socketCliente;

}

Usuario *Cliente::obtenerUsuario() {
    return this->usuario;
}

void Cliente::validarUsuario(Usuario* usuario) {
    //Codigo de mensaje 01
    string mensaje = this->procesarMensaje(usuario->getNombre(), usuario->getContrasenia());
    this->enviarMensaje(mensaje);
    cout<<"Mensaje enviado con exito"<<endl;
}
void Cliente::enviarMensaje(string  mensa){
    const void *mensaje = mensa.c_str();
    this->obtenerSocket()->Enviar(obtenerSocketFD(), mensaje, mensa.length());
}

std::string Cliente::recibirMensaje(){
	int largo = stoi(this->socketCliente->Recibir(this->socketFD, 4),nullptr,10);
    string aux = this->socketCliente->Recibir(this->socketFD, largo);
	return aux;
}
/*Este procesador, codifica el mensaje con el codigo 1.
<código_mensaje>/<usuario>/<password>*/

string Cliente::procesarMensaje(string usuario, string contrasenia) {
    string stringACrear, stringProcesado;
    string separador = "/";
    stringACrear = separador + "1" + separador + usuario + separador + contrasenia;
    int largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    return stringProcesado;
}


/*Este procesador, codifica el mensaje con el codigo 2.
<código_mensaje>/<usuario>/<mensaje>

Este procesador, codifica el mensaje con el codigo 3
 <código_mensaje>/<usuario>/<destinatario>/<mensaje>*/
string Cliente::procesarMensaje(Mensaje *mensaje) {
    string stringACrear,stringProcesado;
    string separador = "/";
    if (mensaje->obtenerDestinatario()==""){
        stringACrear = separador + to_string(mensaje->obtenerCodigo()) + separador + mensaje->obtenerEmisor() + separador + mensaje->
        		obtenerTexto();
    } else {
        stringACrear = separador + to_string(mensaje->obtenerCodigo()) + separador + mensaje->obtenerEmisor() + separador + mensaje->obtenerDestinatario() + separador + mensaje->obtenerTexto();
    }
    int largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    return stringProcesado;
}

// Este procesador, codifica el mensaje con el codigo 5
//  <código_mensaje>/<usuario>
string Cliente::procesarMensaje(string usuario) {
    string stringACrear, stringProcesado;
    string separador = "/";
    stringACrear = separador + "5" + separador + usuario;
    int largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    return stringProcesado;
}

string Cliente::agregarPadding(int lenght) {
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

void Cliente::parsearMensaje(std::string datos){

	int i = 0;
	loggear("entro al parsear mensaje",1);
	loggear (datos,1);

	int codigo = stoi(obtenerParametros(datos,&i),nullptr,10);

	loggear("paso el stoi tragico",1 );


	switch(codigo){
        case RUTAMINIMAPA:{
            int x1 = stoi(obtenerParametros(datos,&i),nullptr,10);
            int x2 = stoi(obtenerParametros(datos,&i),nullptr,10);
            int y1 = stoi(obtenerParametros(datos,&i),nullptr,10);
            int y2 = stoi(obtenerParametros(datos,&i),nullptr,10);
            this->actualizarRutaMiniMapa(x1,x2,y1,y2);

        }break;
        case OBJETOSMINIMAPA:{
        	int arbol = stoi(obtenerParametros(datos,&i),nullptr,10);
        	int cartel = stoi(obtenerParametros(datos,&i),nullptr,10);
        	int distancia = stoi(obtenerParametros(datos,&i),nullptr,10);
        	string lado = obtenerParametros(datos,&i);
        	this->actualizarObjetosMiniMapa(arbol,cartel,distancia,lado);
        }break;
        case RUTAMAPA: {
            int longitud = stoi(obtenerParametros(datos, &i), nullptr, 10);
            float curva = stoi(obtenerParametros(datos, &i), nullptr, 10);
            Track.emplace_back(make_pair(longitud*4,curva/4));
            //this->actualizarRutaMapa(longitud,curva);
        }break;
        case OBJETOSMAPA:{
        	int arbol = stoi(obtenerParametros(datos,&i),nullptr,10);
        	int cartel = stoi(obtenerParametros(datos,&i),nullptr,10);
        	int distancia = stoi(obtenerParametros(datos,&i),nullptr,10);
        	string lado = obtenerParametros(datos,&i);
        	this->actualizarObjetosMapa(arbol,cartel,distancia,lado);
        }break;
        case FINMAPAS:{
            this->modelCar = stoi(obtenerParametros(datos,&i),nullptr,10);
            cout<<"Model Car:"<<modelCar<<endl;
            this->cantidadJugadores = stoi(obtenerParametros(datos,&i),nullptr,10);
            this->crearRivales(cantidadJugadores, modelCar);
            this->minimapa->mostrarSegmentos();
            this->minimapaCompleto=true;
            this->mapaCompleto = true;
            this->finDeMapa = true;
        }break;
		case LOGIN:{
            string mensaje = obtenerParametros(datos,&i);
			cout << mensaje << endl;
               if(mensaje.compare("Bienvenido\n") == 0){
                   this->logueado = true;
               }
		}
			break;
		case BROADCAST:{
            std::string usuario = obtenerParametros(datos,&i);
			std::string mensaje = obtenerParametros(datos,&i);
            string msg = armarMensaje(usuario,mensaje);
            this->colaChat.push_back(msg);
		}
			break;
		case BUZON:{
            std::string usuario = obtenerParametros(datos,&i);
			std::string destinatario = obtenerParametros(datos,&i);
			std::string mensaje = obtenerParametros(datos,&i);
            string msg = armarMensaje(usuario, mensaje);
            string buzon = "[BUZON]" + msg;
            this->colaBuzon.push_back(buzon);
            break;
		}
            case ERROR:{
                cout << "Se desconecto del servidor" << endl;
                this->logueado = false;
                this->conectado = false;
                this->obtenerSocket()->CerrarConexion(this->obtenerSocketFD());
                this->vaciarColaChat();
                this->vaciarColaBuzon();
        }
			break;
            case GO:{
                mover=true;
            }break;
            case STOP:{
                mover=false;
                cout<<"NO ME PUEDO MOVER"<<endl;
            }break;
	case CONTEO:{
		this->tiempo = "0:" + obtenerParametros(datos,&i);
	}break;
        case SIGNAL_CONNECT:{
            this->aliveCounter += 1;
            string msgLog = "El contador es: " + to_string(aliveCounter);
            loggear(msgLog,3);
            loggear ("Cliente se encuentra conectado por red", 2);

        }
            break;
        case AUTO_MOVE:{
            parsearCalculos(datos, i);
        }
            break;
        case CAMBIO_DE_PISTA:{
            cantidadJugadores = stoi(obtenerParametros(datos,&i),nullptr,10);
            for(int k = 0; k < cantidadJugadores; k++){
                string pistaActual = obtenerParametros(datos,&i);
                string usuario = obtenerParametros(datos,&i);
                string scoreEtapa = obtenerParametros(datos,&i);
                string scoreTotal = obtenerParametros(datos,&i);
                scores puntajes;
                puntajes.pistaActual = pistaActual;
                puntajes.scoreEtapa = scoreEtapa;
                puntajes.scoreTotal = scoreTotal;
                this->scoresUsuarios->push_back(pair<string,scores>(usuario,puntajes));
            }
        	//setear variables de control para dejar de pintar y limpiar la lista de rivales
        	this->minimapaCompleto = false;
        	this->mapaCompleto = false;
//        	this->rivalList.clear();
        	this->finDeMapa = false;
        	//limpiamos las rutas
        	this->Track.clear();
        	this->minimapa->limpiarMinimapa();
        	this->mapa->limpiarMapa();
        	cout<<"limpie las pistas"<<endl;
        }
        	break;
		default:
			break;
	}

}

bool Cliente::estalogueado(){
    return this->logueado;
}

string Cliente::armarMensaje(string emisor, string mensaje) {
    string msgADevolver = emisor + ": " + mensaje;
    return msgADevolver;
}

list<string> Cliente::obtenerColaChat() {
    return this->colaChat;
}

void Cliente::desencolarColaChat() {
    colaChat.pop_front();
}

list<string> Cliente::obtenerColaBuzon() {
    return this->colaBuzon;
}


void Cliente::desloguearse(){
    this->logueado = false;
}
void Cliente::desencolarColaBuzon() {
    colaBuzon.pop_front();
}

void Cliente::verBuzon() {

    if (!this->estalogueado()){
        cout<< "Debe loguearse para ver su buzon"<< endl;
        return;
    }
    for (auto it=this->colaBuzon.begin(); it != this->colaBuzon.end(); it++) {
        cout <<*it<<endl;
    }
}


bool Cliente::estaConectado(){
    return this->conectado;
}

bool Cliente::estaConectadoYLogueado(){
    if(!estaConectado()){
        cout<< "Debe conectarse previamente" <<endl;
        return false;
    }

    if(!estalogueado()){
        cout<< "Debe loguearse previamente" <<endl;
        return false;
    }

    return true;
}

void Cliente::conectarse(){
    this->conectado = true;
}

void Cliente::desconectarse(){
    this->conectado = false;
}


void Cliente::vaciarColaChat(){
    while(!this->colaChat.empty()){
        colaChat.pop_front();
    }
}

void Cliente::vaciarColaBuzon(){
    while(!this->colaBuzon.empty()){
        colaBuzon.pop_front();
    }
}

int Cliente::obtenerAliveCounter() {
    return this->aliveCounter;
}

list<pair<int, float>> Cliente::obtenerTrack() {
    return this->Track;
}

void Cliente::actualizarRutaMapa(int longitud, int curva){
	Segmento* segmentoMapa = new Segmento();
	segmentoMapa->setCurva(curva);
	segmentoMapa->setLongitud(longitud);
	this->mapa->agregarSegmento(segmentoMapa);
}

void Cliente::actualizarObjetosMapa(int arbol, int cartel, int distancia, string lado){
	Objeto* objetoMapa = new Objeto();
	objetoMapa->setArbol(arbol);
	objetoMapa->setCartel(cartel);
	objetoMapa->setDistancia(distancia);
	objetoMapa->setLado(lado);
    this->mapa->agregarObjeto(objetoMapa);
}

Mapa *Cliente::obtenerMapa() {
    return this->mapa;
}

void Cliente::setPosY(int posy) {
    this->posY = posy;

}

void Cliente::setPosX(int posx) {
    this->posX = posx;

}

int Cliente::getPosition() {
    return posY;
}

int Cliente::getX() {
    return posX;
}

Minimapa* Cliente::getMinimapa(){
    return this->minimapa;
}

bool Cliente::recibioFinDeMapa() {
    return finDeMapa;
}

int Cliente::obtenerModel() {
    return modelCar;
}

int Cliente::obtenerCantidadJugadores() {
    return cantidadJugadores;
}

void Cliente::parsearCalculos(string datos, int i) {
    int posY = stoi(obtenerParametros(datos,&i),nullptr,10);
    int posX = stoi(obtenerParametros(datos,&i),nullptr,10);
    int velocidad = stoi(obtenerParametros(datos,&i),nullptr,10);
    string tiempo_aux= obtenerParametros(datos,&i);
    if (tiempo_aux != "" && tiempo_aux != " " && tiempo_aux != "\0")
    	this->tiempo = tiempo_aux;
    this->destrozo = stoi(obtenerParametros(datos,&i),nullptr,10);
    //cout<<"Nivel de destrozo:"<<this->destrozo<<endl;
    this->setPosY(posY);
    this->setPosX(posX);
    this->setVelocidad(velocidad);
    cantidadJugadores = stoi(obtenerParametros(datos,&i),nullptr,10);
    for(int k = 0; k < cantidadJugadores; k++){
        int player = stoi(obtenerParametros(datos,&i),nullptr,10);
        int x = stoi(obtenerParametros(datos,&i),nullptr,10);
        int y = stoi(obtenerParametros(datos,&i),nullptr,10);
        Posicion* pos = new Posicion(x,y);
        this->minimapa->setAutoEnRadar(player,pos);
    }
    cantidadADibujar = stoi(obtenerParametros(datos,&i),nullptr,10);
    int j=0;

    for(list<Rival*>::iterator it = this->rivalList.begin(); it != this->rivalList.end();++it){
        Rival* rival = *it;
        if (j< cantidadADibujar){
            int playerNum = stoi(obtenerParametros(datos,&i),nullptr,10);
            int playerDestroy = stoi(obtenerParametros(datos,&i),nullptr,10);
            int playerPosX = stoi(obtenerParametros(datos,&i),nullptr,10);
            float playerPosY = stoi(obtenerParametros(datos,&i),nullptr,10);
            //if (!rival->getDibujar()){
                rival->actualizar(playerNum,playerDestroy,playerPosX,playerPosY);
            //}
        } else rival->notDibujar();
        j++;
    }

}

int Cliente::cantidadAdibujar() {
    return cantidadADibujar;
}

void Cliente::crearRivales(int cantRivales, int miAuto) {
    switch (cantRivales){
        case 2:{
            Rival* rival = new Rival();
            rivalList.emplace_back(rival);
        }
        break;
        case 3:{
            Rival* rival1 = new Rival();
            Rival* rival2 = new Rival();
            rivalList.emplace_back(rival1);
            rivalList.emplace_back(rival2);
        }
        break;
        case 4:{
            Rival* rival1 = new Rival();
            Rival* rival2= new Rival();
            Rival* rival3 = new Rival();
            rivalList.emplace_back(rival1);
            rivalList.emplace_back(rival2);
            rivalList.emplace_back(rival3);
        }break;
    }


}

/*int Cliente::setRival(string datos, int i) {
    int playerNum = stoi(obtenerParametros(datos,&i),nullptr,10);
    int playerPosX = stoi(obtenerParametros(datos,&i),nullptr,10);
    float playerPosY = stoi(obtenerParametros(datos,&i),nullptr,10);
    for(list<Rival*>::iterator it = this->rivalList.begin(); it != this->rivalList.end();++it){
        Rival* rival = *it;
        if (!rival->getDibujar()){
            rival->actualizar(playerNum,playerPosX,playerPosY);
        }
    }
    return i;

}*/

int Cliente::obtenerCantidadDePlayersADibujar() {
    return cantidadADibujar;
}

list<Rival *> Cliente::obtenerRivalList() {
    return rivalList;
}

int Cliente::getY() {
    return posY;
}

void Cliente::setVelocidad(int vel){
    this->velocidad = vel;
}

int Cliente::getVelocidad(){
   return this->velocidad;
}

string Cliente::getTiempo(){
   return this->tiempo;
}

bool Cliente::sePuedeMover(){
	return this->mover;
}

int Cliente::getDestrozo() {
    return this->destrozo;
}

void Cliente::setRecibioFinDeMapa() {
    this->finDeMapa = false;

}


list<pair<string,scores>>* Cliente::getScores(){
    return this->scoresUsuarios;
}

void Cliente::setFinDeMapa(bool finDeMapa){
    this->finDeMapa = finDeMapa;
}