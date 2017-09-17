#include "../../headers/Model/servidor.h"
#include "../../headers/Model/logger.h"

#define LOGIN 1
#define BROADCAST 2
#define BUZON 3

Servidor::Servidor(){

	this->cantidadDeConexiones = 0;
	this->puerto = 0;
	this->puerto2 = 8010; //HARDCODE PARA SEGUNDO CLIENTE
	this->baseDeDatos = NULL;
	this->serverSocket= new Socket();
	this->serverSocket2 = new Socket();
	//this->socketEscucha=0;
	this->conexiones = 0;
	this->socketFD = 0;
	this->socketFD2 = 0;
}

//HCD
Socket* Servidor::obtenerSocket2(){
	return this->serverSocket2;
}
int Servidor::getSocketFD(){
	return this->socketFD;
}

void Servidor::setSocketFD(int fd){
	this->socketFD = fd;
}

int Servidor::getPuerto2(){
	return this->puerto2;
}

//

int Servidor::getSocketFD2(){
	return this->socketFD2;
}

void Servidor::setSocketFD2(int fd2){
	this->socketFD2 = fd2;
}

int Servidor::getCantidadDeConexiones(){

	return this->cantidadDeConexiones;
}

int Servidor::getPuerto(){

	return this->puerto;
}

void Servidor::setCantidadDeConexiones(int cantidadDeConexiones){

	this->cantidadDeConexiones = cantidadDeConexiones;
}

void Servidor::setPuerto(int puerto){

	this->puerto = puerto;
}

void Servidor::setBaseDeDatos(BaseDeDatos* baseDeDatos){
	this->baseDeDatos = baseDeDatos;
}

BaseDeDatos* Servidor::getBaseDeDatos(){
	return this->baseDeDatos;
}

void Servidor::mostrarUsuariosDisponibles(){

	this->baseDeDatos->mostrarTodosLosUsuarios();
}


Socket* Servidor::obtenerSocket(){
    return this->serverSocket;
}

void Servidor::abrirConexiones(){

	Thread conexion1;
	conexion1.crear(IniciarConexiones,this);
	Thread conexion2;
	conexion2.crear(IniciarConexiones2,this);
}


void Servidor::iniciarServidor() {
    cout<<"El puerto del servidor es: "<<this->getPuerto()<<endl;
    setSocketFD2(obtenerSocket()->Crear()); //devuelve el file descriptor
    obtenerSocket()->Enlazar(this->getSocketFD2(),this->getPuerto());
   	obtenerSocket()->Escuchar(this->getSocketFD2(),this->getCantidadDeConexiones());
	cout << "Escuchando conexiones ..." << endl;
	
}


void Servidor::aceptarConexiones() {
	this->setSocketFD2(obtenerSocket()->AceptarConexion(this->getSocketFD2()));
	cout << "Conexion aceptada" << endl;
	this->conexiones += 1;
}


void Servidor::finalizarConexiones() {
	obtenerSocket()->CerrarConexion(this->getSocketFD2());
	cout << "Cerrando conexiones" << endl;
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

std::string Servidor::recibirMensaje(){
	int largo = stoi(this->serverSocket->Recibir(this->socketFD2, 4),nullptr,10);
	cout<<"paso el stoi"<<endl;
	return this->serverSocket->Recibir(this->socketFD2, largo);
}

void Servidor::enviarMensaje(string  mensa){
    const void *mensaje = mensa.c_str();
    this->obtenerSocket()->Enviar(getSocketFD2(), mensaje, mensa.length());
}


void Servidor::parsearMensaje(std::string datos){

	int i = 0;
	loggear("entro al parsear mensaje",1);
	loggear (datos,1);
	int codigo = stoi(obtenerParametros(datos,&i),nullptr,10);
	loggear("paso el stoi tragico",1 );
	std::string usuario = obtenerParametros(datos,&i);

	switch(codigo){
		case LOGIN:{

			std::string password = obtenerParametros(datos,&i);
			this->conexiones += 1;
		}

			break;
		case BROADCAST:{
			std::string mensaje = obtenerParametros(datos,&i);
		}
			break;
		case BUZON:{
			std::string destinatario = obtenerParametros(datos,&i);
			std::string mensaje = obtenerParametros(datos,&i);
		}
			break;
		default:
			break;
	}

}

void Servidor::validarCliente(string usuario, string contrasenia) {
	Usuario* usuarioAValidar = this->obtenerBaseDeDatos()->getUsuario(usuario);
	if (usuarioAValidar==NULL){
		//Enviar mensaje de error al cliente
		//Actividad de loggeo incorrecto en logger
	} else {
			if (usuarioAValidar->estaConectado()== true) {
				//Enviar mensaje de error al cliente
				//Actividad de loggeo incorrecto en logger
			}else{
				//Enviar el mensaje al cliente para que pueda continuar con su actividad
				//Actividad de loggeo correcto en logger.
			}
	}

}

void Servidor::mostrarUsuariosConectados(){
    cout<< this->conexiones << endl;
}

BaseDeDatos *Servidor::obtenerBaseDeDatos() {
	return this->baseDeDatos;
}


void *Servidor::IniciarConexiones2(void* servidor){

	Servidor* srv = (Servidor*) servidor;
	srv->iniciarServidor2();
	srv->aceptarConexiones2();
	pthread_exit(NULL);
}

void *Servidor::IniciarConexiones(void* servidor){

	Servidor* srv = (Servidor*) servidor;
	srv->iniciarServidor();
	srv->aceptarConexiones();
	pthread_exit(NULL);
}

void Servidor::iniciarServidor2(){
	cout<<"El puerto del servidor es: "<<this->getPuerto2()<<endl;
	setSocketFD(obtenerSocket2()->Crear()); //devuelve el file descriptor
	obtenerSocket2()->Enlazar(this->getSocketFD(),this->getPuerto2());
	obtenerSocket2()->Escuchar(this->getSocketFD(),this->getCantidadDeConexiones());
	cout << "Escuchando conexiones ..." << endl;
}

void Servidor::aceptarConexiones2(){

	this->setSocketFD(obtenerSocket2()->AceptarConexion(this->getSocketFD()));
	cout << "Conexion aceptada" << endl;
	this->conexiones += 1;
}

//DEBE BORRAR LA MEMORIA QUE PIDIO EL BUILDER PARA LA BASE DE DATOS.
Servidor::~Servidor(){
	//this->finalizarConexiones();
	delete this->baseDeDatos;
}
