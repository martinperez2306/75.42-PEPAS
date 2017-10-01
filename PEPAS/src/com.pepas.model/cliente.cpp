#include "../../headers/com.pepas.model/cliente.h"
#include "../../headers/com.pepas.logger/Logger.h"

#define LOGIN 4
#define BROADCAST 2
#define BUZON 3
#define SERVIDOR 4
#define ERROR 5

Cliente::Cliente() {
    this->socketCliente = new Socket();
    this->usuario = new Usuario();
    this->socketFD=0;
    this->logueado = false;
    this->conectado = false;
    
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

void Cliente::logIn(){
    if(this->logueado){
        cout << "Usted ya esta logueado" << endl;
        return;
    }
    string usuario;
    string clave;
    cout<<"Ingrese su nombre de usuario"<<endl;
    cin>> usuario;
    cout<<"Ingrese su clave"<<endl;
    cin>> clave;
    this->obtenerUsuario()->setearNombre(usuario);
    this->obtenerUsuario()->setearContrasenia(clave);
    this->validarUsuario(obtenerUsuario());
    //this->parsearMensaje(this->recibirMensaje());
 
}

int Cliente::conectarseAlServidor(const char *ip, int puerto) {
    this->socketFD = this->socketCliente->Crear();
    cout<<"Socket creado... Conectando..."<<endl;
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
                cout << "Se desconecto el servidor" << endl;
                this->logueado = false;
                this->conectado = false;
                this->obtenerSocket()->CerrarConexion(this->obtenerSocketFD());
                this->vaciarColaChat();
                this->vaciarColaBuzon();
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