#include "../../headers/Model/servidor.h"
#include "../../headers/Model/logger.h"

#define LOGIN 1
#define BROADCAST 2
#define BUZON 3

Servidor::Servidor(){

	this->cantidadDeConexiones = 0;
	this->puerto = 0;
    //HARDCODE PARA SEGUNDO CLIENTE
	this->baseDeDatos = NULL;
	this->serverSocket= new Socket();
	this->serverSocket2 = new Socket();
	this->conexiones = 0;
	this->socketEscucha = 0;
	this->socketFD = 0;
}

//HCD

int Servidor::obtenerSocketEscucha(){
	return this->socketEscucha;
}

void Servidor::asignarSocketEscucha(int fd){
	this->socketEscucha = fd;
}



int Servidor::obtenerSocketFD(){
	return this->socketFD;
}

void Servidor::asignarSocketFD(int fd2){
	this->socketFD = fd2;
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

	//Thread conexion1;
	//conexion1.crear(IniciarConexiones,this);
/*	Thread conexion2;
	conexion2.crear(IniciarConexiones2,this);*/
}


void Servidor::iniciarServidor() {
    cout<<"El puerto del servidor es: "<<this->getPuerto()<<endl;
    asignarSocketEscucha(obtenerSocket()->Crear()); //devuelve el file descriptor
    obtenerSocket()->Enlazar(this->obtenerSocketEscucha(),this->getPuerto());
   	obtenerSocket()->Escuchar(this->obtenerSocketEscucha(),this->getCantidadDeConexiones());
	cout << "Escuchando conexiones ..." << endl;
}


void Servidor::aceptarConexiones() {
    int fd = obtenerSocket()->AceptarConexion(this->obtenerSocketEscucha());
    this->agregarAlistaDeConexiones(fd);
    cout << "Conexion aceptada" << endl;
    this->conexiones += 1;
}


void Servidor::finalizarConexiones() {
	obtenerSocket()->CerrarConexion(this->obtenerSocketFD());
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
	int largo = stoi(this->serverSocket->Recibir(this->obtenerSocketFD(), 4),nullptr,10);
	cout<<"paso el stoi"<<endl;
	return this->serverSocket->Recibir(this->obtenerSocketFD(), largo);
}

void Servidor::enviarMensaje(string  mensa){
    const void *mensaje = mensa.c_str();
    this->obtenerSocket()->Enviar(obtenerSocketFD(), mensaje, mensa.length());
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


void *Servidor::IniciarConexiones(void* servidor){

	Servidor* srv = (Servidor*) servidor;
	srv->iniciarServidor();
	srv->aceptarConexiones();
	srv->parsearMensaje(srv->recibirMensaje());
    cout<<"Termino parseo"<<endl;
    string msg = "0009/1/dale/e";
    srv->enviarMensaje(msg);
    srv->aceptarConexiones();
    srv->parsearMensaje(srv->recibirMensaje());
	pthread_exit(NULL);
}




//DEBE BORRAR LA MEMORIA QUE PIDIO EL BUILDER PARA LA BASE DE DATOS.
Servidor::~Servidor(){
	//this->finalizarConexiones();
	delete this->baseDeDatos;
}

void Servidor::agregarAlistaDeConexiones(int nuevaConexion) {
    if (socketFD == 0) {
        this->asignarSocketFD(nuevaConexion);
    }else{
        int socketTest =  nuevaConexion;
    }
}
