#include "../../headers/com.pepas.model/cliente.h"
#include "../../headers/com.pepas.logger/Logger.h"
#include "../../headers/com.pepas.view/vista.h"


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
    posX =  1024/2 -100;

}
bool Cliente::minimapaEstaCompleto(){
    return (this->minimapaCompleto);
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
            Track.emplace_back(make_pair(longitud,curva));
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
        	this->mapa->mostrarSegmentos();
        	this->mapa->mostrarObjetos();
        	this->minimapa->mostrarSegmentos();
        	this->minimapa->mostrarObjetos();
            this->minimapaCompleto=true;
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
        case SIGNAL_CONNECT:{
            this->aliveCounter += 1;
            string msgLog = "El contador es: " + to_string(aliveCounter);
            loggear(msgLog,3);
            loggear ("Cliente se encuentra conectado por red", 2);

        }
            break;
        case AUTO_MOVE:{
            int posY = stoi(obtenerParametros(datos,&i),nullptr,10);
            int posX = stoi(obtenerParametros(datos,&i),nullptr,10);
            this->setPosY(posY);
            this->setPosX(posX);

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
