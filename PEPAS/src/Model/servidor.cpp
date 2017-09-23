#include "../../headers/Model/servidor.h"
#include "../../headers/Model/logger.h"

#define LOGIN 1
#define BROADCAST 2
#define BUZON 3



std::list<int> crearPuertos(){
	
	std::list<int> puertos;
	for(int i = 8000; i <= 8007; i++)
		puertos.push_back(i);

	return puertos;
	
}

Servidor::Servidor(){

	this->cantidadDeConexiones = 0;
	this->puerto = 0;
	this->baseDeDatos = NULL;
	this->serverSocket= new Socket();
	this->conexiones = 0;
	this->socketEscucha = 0;
	this->socketFD = 0;
	this->puertosDisponibles = crearPuertos();
	this->terminado = false;


}



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

// void Servidor::iniciarServidor() {
//     cout<<"El puerto del servidor es: "<<this->getPuerto()<<endl;
//     asignarSocketEscucha(obtenerSocket()->Crear()); //devuelve el file descriptor
//     obtenerSocket()->Enlazar(this->obtenerSocketEscucha(),this->getPuerto());
   	
// }

// int Servidor::iniciarConexion(int puerto) {
// 	Socket* newSocket= new Socket();
//     cout<<"El puerto del cliente es: "<<puerto<<endl;
//     int fd = newSocket->Crear();
//     newSocket->Enlazar(fd,puerto);
//     newSocket->Escuchar(fd,this->getCantidadDeConexiones());
// 	//cout << "Escuchando conexiones ..." << endl;
//     fd = newSocket->AceptarConexion(fd);
//     mapFD.insert({puerto,fd});
//     /*Agrego a la lista el puerto que estoy usando*/
//     puertosEnUso.push_back(puerto);
//     this->conexiones += 1;
//     cout << "Conexion aceptada" << endl;
//     int fd = this->obtenerSocket()->Crear();
//     this->obtenerSocket()->Enlazar(fd,puerto);
//     this->obtenerSocket()->Escuchar(fd,this->getCantidadDeConexiones());
//     cout << "Escuchando conexiones ..." << endl;
//     fd = this->obtenerSocket()->AceptarConexion(fd);
//     mapFD.insert({puerto,fd});
//     this->conexiones +=1;
//     cout << "Conexion aceptada" << endl;
//     return fd;
// }


// int  Servidor::aceptarConexiones() {
// 	obtenerSocket()->Escuchar(this->obtenerSocketEscucha(),this->getCantidadDeConexiones());
// 	cout << "Escuchando conexiones ..." << endl;
//     int fd = obtenerSocket()->AceptarConexion(this->obtenerSocketEscucha());
//     cout << "Conexion aceptada" << endl;
    
//     int puerto = this->puertosDisponibles.front();
//     cout << puerto << endl;
//     this->puertosDisponibles.pop_front();
//     this->asignarSocketFD(fd);
//     this->enviarMensaje(to_string(puerto));
//     int socketNuevo = this->iniciarConexion(puerto);
//     /*Cierro la conexion con el socket escucha*/
//     obtenerSocket()->CerrarConexion(fd);


//     return socketNuevo;
// }

void Servidor::iniciarServidor() {
	/*Aqui se crea el socket escucha del servidor el cual es leido del XML*/
    cout<<"El puerto del servidor es: "<<this->getPuerto()<<endl;
    asignarSocketEscucha(obtenerSocket()->Crear()); //devuelve el file descriptor
    obtenerSocket()->Enlazar(this->getPuerto());
   	
}

Socket* Servidor::iniciarConexion(int puerto) {
	Socket* newSocket= new Socket();
    cout<<"El puerto del cliente es: "<<puerto<<endl;
    newSocket->Crear();
    newSocket->Enlazar(puerto);
    newSocket->Escuchar(this->getCantidadDeConexiones());
	//cout << "Escuchando conexiones ..." << endl;
    int fd = newSocket->AceptarConexion();
    mapFD.insert({puerto,fd});
    /*Agrego a la lista el puerto que estoy usando*/
    puertosEnUso.push_back(puerto);
    /*Piso el valor del fd por el nuevo que contiene la conexion aceptada*/
	newSocket->asignarFD(fd);
    cout << "Conexion aceptada" << endl;
    return newSocket;
}


Socket*  Servidor::aceptarConexiones() {
	//cout << this->socketEscucha << endl;
	cout << "Escuchando conexiones ..." << endl;
	obtenerSocket()->Escuchar(this->obtenerSocketEscucha(),this->getCantidadDeConexiones());
    int fd = obtenerSocket()->AceptarConexion();
    cout << "Conexion aceptada" << endl;
	/*Toma un puerto de los disponibles*/
    int puerto = this->puertosDisponibles.front();
    cout << puerto << endl;
	/*Lo quita de la pila*/ //TODO CUANDO UN CLIENTE SE DESCONECTA DEBERIA VOLVER A AGREGARLO A LA LISTA.
	this->puertosDisponibles.pop_front();
    this->asignarSocketFD(fd);
	this->obtenerSocket()->asignarFD(fd);
	/*Envia un mensaje al cliente con el nuevo puerto al que se debe conectar*/
    this->enviarMensaje(to_string(puerto), this->obtenerSocket());

    Socket* socketNuevo = this->iniciarConexion(puerto);
    /*Cierro la conexion con el socket escucha*/
    obtenerSocket()->CerrarConexion(fd);
    this->obtenerSocket()->asignarFD(this->obtenerSocketEscucha());



    return socketNuevo;
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

std::string Servidor::recibirMensaje(Socket* socket){
	int largo = stoi(socket->Recibir(4),nullptr,10);
	cout<<"paso el stoi"<<endl;
	return socket->Recibir(largo);
}

void Servidor::enviarMensaje(string  mensa, Socket* socket){
    const void *mensaje = mensa.c_str();
    socket->Enviar(mensaje, mensa.length());
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




//DEBE BORRAR LA MEMORIA QUE PIDIO EL BUILDER PARA LA BASE DE DATOS.
Servidor::~Servidor(){
	//this->finalizarConexiones();
	delete this->baseDeDatos;
}
//TODO CERRARSOCKETS
void Servidor::cerrarSockets() {
    //*Recorro lista de puertos y hasheo el puerto con el socket*//*
  /*  while (!puertosEnUso.empty()){
        int puertoActual = puertosEnUso.front();
        puertosEnUso.pop_front();
        unordered_map<int,int>::const_iterator got = mapFD.find(puertoActual);
        this->obtenerSocket()->CerrarSocket(got->second);
    }
*/

	this->obtenerSocket()->CerrarConexion(obtenerSocketEscucha());

}

bool Servidor::getTerminado() {
	return this->terminado;
}



