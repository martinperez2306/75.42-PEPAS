#include "../../headers/Model/servidor.h"

#define LOGIN 1
#define BROADCAST 2
#define BUZON 3



Servidor::Servidor(){

	this->cantidadDeConexiones = 0;
	this->puerto = 0;
	this->baseDeDatos = NULL;
	this->serverSocket= new Socket();
	this->socketEscucha=0;
	parsearMensaje("0020/2/usuario/11111");

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

int Servidor::obtenerSocketFD() {
    return this->socketEscucha;
}


void Servidor::asignarSocketFd(int socket) {
	this->socketEscucha=socket;
}


void Servidor::iniciarServidor() {
    cout<<"El puerto del servidor es: "<<this->getPuerto()<<endl;
    asignarSocketFd(obtenerSocket()->Crear()); //devuelve el file descriptor
    obtenerSocket()->Enlazar(this->obtenerSocketFD(),this->getPuerto());
   	obtenerSocket()->Escuchar(this->obtenerSocketFD(),this->getCantidadDeConexiones());
	cout << "Servidor creado correctamente, escuchando conexiones ..." << endl;
	
}



void Servidor::aceptarConexiones() {
	obtenerSocket()->AceptarConexion(this->obtenerSocketFD());
	cout << "Conexion aceptada" << endl;
}


void Servidor::finalizarConexiones() {
	obtenerSocket()->CerrarConexion(this->obtenerSocketFD());
	cout << "Cerrando conexiones" << endl;
}

std::string obtenerParametros(std::string mensaje, int tamanio, int* i){
	std::string aux = "";
		while(*i != tamanio){
			aux = aux + mensaje[*i];
			*i = *i + 1;
			if (mensaje[*i] == '/'){
				*i = *i + 1;
				break;
			}

		}
	return aux;

}


void Servidor::parsearMensaje(std::string datos){

	int i = 0;
	int tam = stoi(obtenerParametros(datos,4,&i),nullptr,10);
	int codigo = stoi(obtenerParametros(datos,tam,&i),nullptr,10);

	switch(codigo){
		case LOGIN:{
			std::string usuario = obtenerParametros(datos,tam,&i);
			std::string password = obtenerParametros(datos,tam,&i);
		}
			
		break;
		case BROADCAST:{
			std::string usuario = obtenerParametros(datos,tam,&i);
			std::string mensaje = obtenerParametros(datos,tam,&i);
			cout << usuario << endl;
			cout << mensaje << endl;
		}
		break;
		case BUZON:{
			std::string usuario = obtenerParametros(datos,tam,&i);
			std::string destinatario = obtenerParametros(datos,tam,&i);
			std::string mensaje = obtenerParametros(datos,tam,&i);
		}
		break;
		default:
		break;
	}

}






//DEBE BORRAR LA MEMORIA QUE PIDIO EL BUILDER PARA LA BASE DE DATOS.
Servidor::~Servidor(){

	delete this->baseDeDatos;
}
