#include "../../headers/Model/servidor.h"
#include "../../headers/Model/logger.h"

#define LOGIN 1
#define BROADCAST 2
#define BUZON 3
#define LOGOUT 5
#define USER_DISCONNECT 6
#define RECONETION_FAIL 8

typedef pair<int, Socket*> socketConect;

std::list<int> crearPuertos(){
	
	std::list<int> puertos;
	for(int i = 8000; i <= 8007; i++)
		puertos.push_back(i);

	return puertos;
	
}

Servidor::Servidor(){

    this->cantidadMaximaDeConexiones = 0;
	this->puerto = 0;
	this->baseDeDatos = NULL;
	this->serverSocket= new Socket();
	this->conexiones = 0;
	this->socketEscucha = 0;
	this->socketFD = 0;
	this->puertosDisponibles = crearPuertos();
	this->terminado = false;
	this->mapaSocket = new map<int,Socket*>();

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

int Servidor::getCantidadMaximaDeConexiones(){

    return this->cantidadMaximaDeConexiones;
}

int Servidor::getPuerto(){

	return this->puerto;
}

void Servidor::setCantidadMaximaDeConexiones(int cantidadMaximaDeConexiones) {
    this->cantidadMaximaDeConexiones = cantidadMaximaDeConexiones;
}
void Servidor::mostrarTodosLosUsuariosConectados(){
    this->baseDeDatos->mostrarTodosLosUsuariosConectados();
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


void Servidor::iniciarServidor() {
	/*Aqui se crea el socket escucha del servidor el cual es leido del XML*/
    string msg = "El puerto del servidor es: " + to_string(this->getPuerto());
    loggear (msg,1);
    asignarSocketEscucha(obtenerSocket()->Crear()); //devuelve el file descriptor
    obtenerSocket()->Enlazar(this->getPuerto());
   	
}

Socket* Servidor::iniciarConexion(int puerto) {
	Socket* newSocket= new Socket();
    string msg = "El puerto del cliente es: " + to_string(puerto);
    loggear (msg, 1);
    newSocket->Crear();
    newSocket->Enlazar(puerto);
    newSocket->Escuchar(this->getCantidadMaximaDeConexiones());
    int fd = newSocket->AceptarConexion();
    mapFD.insert({puerto,fd});
    /*Agrego a la lista el puerto que estoy usando*/
    puertosEnUso.push_back(puerto);
    /*Piso el valor del fd por el nuevo que contiene la conexion aceptada*/
	newSocket->asignarFD(fd);
    loggear ("Conexion aceptada", 1);
    return newSocket;
}


/*
Socket*  Servidor::aceptarConexiones() {
    loggear ("Escuchando conexiones",1);
	obtenerSocket()->Escuchar(this->obtenerSocketEscucha(),this->getCantidadDeConexiones());
    int fd = obtenerSocket()->AceptarConexion();
    loggear ("Conexion aceptada" , 1);
	*/
/*Toma un puerto de los disponibles*//*

    int puerto = this->puertosDisponibles.front();
    string msg = "Conexion nueva en puerto: " + to_string(puerto);
    loggear(msg,1);
	*/
/*Lo quita de la pila*//*
 //TODO CUANDO UN CLIENTE SE DESCONECTA DEBERIA VOLVER A AGREGARLO A LA LISTA.
	this->puertosDisponibles.pop_front();
    this->asignarSocketFD(fd);
	this->obtenerSocket()->asignarFD(fd);
	*/
/*Envia un mensaje al cliente con el nuevo puerto al que se debe conectar*//*

    this->enviarMensaje(to_string(puerto), this->obtenerSocket());
    Socket* socketNuevo = this->iniciarConexion(puerto);
    */
/*Cierro la conexion con el socket escucha*//*

    obtenerSocket()->CerrarConexion(fd);
    this->obtenerSocket()->asignarFD(this->obtenerSocketEscucha());

    */
/*Agregamos el socket del cliente y el servidor donde se comunicaran a la lista*//*

    this->mapaSocket->insert(socketConect(puerto,socketNuevo));

    return socketNuevo;
}
*/

Socket*  Servidor::aceptarConexiones() {
    /*Servidor recibe conexion de los clientes en el puerto de escucha*/
    loggear ("Escuchando conexiones",1);
    obtenerSocket()->Escuchar(this->obtenerSocketEscucha(),this->getCantidadMaximaDeConexiones());
    int fd = obtenerSocket()->AceptarConexion();
    loggear ("Conexion aceptada" , 1);
    this->asignarSocketFD(fd);
    this->obtenerSocket()->asignarFD(fd);
    /*Valida que no se haya llegado al maximo de conexiones*/
    if(this->conexiones == this->cantidadMaximaDeConexiones){
        string msgError = "El servidor ha llegado a su maxima capacidad de conexiones.";
        this->enviarMensaje(to_string(RECONETION_FAIL),this->obtenerSocket());
        this->obtenerSocket()->CerrarConexion(fd);
        this->obtenerSocket()->asignarFD(this->obtenerSocketEscucha());
        loggear(msgError,1);
        return this->obtenerSocket();
    }else{
        /*Toma un puerto de los disponibles*/
        int puerto = this->puertosDisponibles.front();
        string msg = "Conexion nueva en puerto: " + to_string(puerto);
        loggear(msg,1);
        /*Lo quita de la pila*/ //TODO CUANDO UN CLIENTE SE DESCONECTA DEBERIA VOLVER A AGREGARLO A LA LISTA.
        this->puertosDisponibles.pop_front();
        /*Envia un mensaje al cliente con el nuevo puerto al que se debe conectar*/
        this->enviarMensaje(to_string(puerto), this->obtenerSocket());
        Socket* socketNuevo = this->iniciarConexion(puerto);
        /*Cierro la conexion con el socket escucha*/
        obtenerSocket()->CerrarConexion(fd);
        this->obtenerSocket()->asignarFD(this->obtenerSocketEscucha());
        /*Agregamos el socket del cliente y el servidor donde se comunicaran a la lista*/
        this->mapaSocket->insert(socketConect(puerto,socketNuevo));
        this->conexiones += 1;
        return socketNuevo;
    }
}

void Servidor::finalizarConexiones() {
	obtenerSocket()->CerrarConexion(this->obtenerSocketFD());
    loggear ("Cerrando conexiones",1 );
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

std::string Servidor::recibirMensaje(Socket* socket) {
    string msg;
    int largo = stoi(socket->Recibir(4), nullptr, 10);
    if (largo == -1) {
        msg = "6"; // codigo 6
        loggear("Se recibio mensaje 0 de desconexion", 1);
    }
    else msg = socket->Recibir(largo);
	return socket->Recibir(largo);
}

void Servidor::enviarMensaje(string  mensa, Socket* socket){
    const void *mensaje = mensa.c_str();
    string msgLogger = "Mensaje enviado: " + mensa;
    loggear (msgLogger,1);
    socket->Enviar(mensaje, mensa.length());
}


string Servidor::parsearMensaje(std::string datos, Socket* socketDelemisor){

	int i = 0;
	loggear("Entro al parsear mensaje",1);
	loggear (datos,1);
	int codigo = stoi(obtenerParametros(datos,&i),nullptr,10);
	loggear("Paso el stoi tragico",1 );
	std::string usuario = obtenerParametros(datos,&i);
    string mensajeAEnviar;

	switch(codigo){
		case LOGIN:{
			std::string password = obtenerParametros(datos,&i);
            mensajeAEnviar = validarCliente(usuario, password, socketDelemisor);
            enviarMensaje(mensajeAEnviar, socketDelemisor);
		}
			break;
		case BROADCAST:{
			std::string mensaje = obtenerParametros(datos,&i);
			map<int,Socket*>::iterator iterador;
			for (iterador = mapaSocket->begin(); iterador != mapaSocket->end(); ++iterador){
                    unsigned long largoDelMensaje = datos.length();
                    string stringProcesado = this->agregarPadding(largoDelMensaje) + datos;
				    this->enviarMensaje(stringProcesado,iterador->second);
				}
		}
			break;
		case BUZON:{
            string msg;
			std::string destinatario = obtenerParametros(datos,&i);
			std::string mensaje = obtenerParametros(datos,&i);
            Usuario *usuarioDestinatario = this->obtenerBaseDeDatos()->getUsuario(destinatario);
            Usuario *usuarioEstaConectado = this->obtenerBaseDeDatos()->getUsuarioConectado(destinatario);
            if (usuarioDestinatario == NULL || usuarioEstaConectado == NULL) {
                msg = "/4/El destinatario no existe o no se encuentra conectado.";
                unsigned long largoDelMensaje = msg.length();
                string stringProcesado = this->agregarPadding(largoDelMensaje) + msg;
                this->enviarMensaje(stringProcesado, this->obtenerBaseDeDatos()->getUsuario(usuario)->getSocket());
            }else{
                unsigned long largoDelMensaje = datos.length();
                string stringProcesado = this->agregarPadding(largoDelMensaje) + datos;
                loggear (stringProcesado,1);
                this->enviarMensaje(stringProcesado,usuarioDestinatario->getSocket());
            }
            break;
		}
        case LOGOUT:{
            string msg = "El usuario se ha deslogueado correctamente";
            msg = procesarMensaje(msg);
            this->enviarMensaje(msg,socketDelemisor);
            Usuario * usuarioLogOut = this->obtenerBaseDeDatos()->getUsuario(usuario);
            usuarioLogOut->estaDesconectado();
            this->obtenerBaseDeDatos()->sacarUsuarioConectadoABaseDeDatos(usuario);
            string msgLogger = "Usuario " + usuario + "desconectado";
            loggear (msgLogger,1);
        }
			break;
        case USER_DISCONNECT:{
            string msg = "Se ha desconectado un usuario";
            loggear (msg,1);
            mensajeAEnviar = "CerrarCliente";

        }
            break;
		default:
			break;
	}
return mensajeAEnviar;
}

string Servidor::validarCliente(string usuario, string contrasenia, Socket* socketDelEmisor) {
    Usuario *usuarioAValidar = this->obtenerBaseDeDatos()->getUsuario(usuario);
    string msg, msgOK, msgAdevolver;
    bool fallo = false;
    if (usuarioAValidar == NULL) {
        msg = "No existe el usuario ingresado";
        loggear(msg, 3);
        msg = procesarMensaje(msg);
        fallo = true;
    } else if(usuarioAValidar->getContrasenia() != contrasenia ||
            usuarioAValidar->getUsuario() != usuario) {
            msg = "Usuario o contraseña incorrectas";
            loggear(msg, 3);
            msg = procesarMensaje(msg);
            fallo = true;
        } else if (usuarioAValidar->getConectado()) {
                msg = "El usuario ingresado ya se encuentra conectado";
                loggear(msg, 3);
                msg = procesarMensaje(msg);
                fallo = true;
            } else {
                msgOK = "Bienvenido\n";
                loggear(msgOK, 1);
                msgOK = procesarMensaje(msgOK);
                usuarioAValidar->estaConectado();
                usuarioAValidar->asignarSocket(socketDelEmisor);
                this->baseDeDatos->agregarUsuarioConectadoABaseDeDatos(usuario);
            }

    msgAdevolver = msgOK;
    if (fallo){
        msgAdevolver = msg;
    }
return msgAdevolver;
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
    while (!puertosEnUso.empty()){
        int puertoActual = puertosEnUso.front();
        puertosEnUso.pop_front();
        unordered_map<int,int>::const_iterator got = mapFD.find(puertoActual);
        this->obtenerSocket()->CerrarConexion(got->second);
        //this->obtenerSocket()->CerrarSocket(got->second);

    }
	this->obtenerSocket()->CerrarConexion(obtenerSocketEscucha());

}

bool Servidor::getTerminado() {
	return this->terminado;
}

string Servidor::agregarPadding(int lenght) {
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


/*Este procesador, codifica el mensaje con el codigo 4.
<código_mensaje>/<mensaje>*/
string Servidor::procesarMensaje(string mensa) {
    string stringACrear, stringProcesado;
    string separador = "/";
    stringACrear = separador + "4" + separador + mensa;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    loggear(stringProcesado,1);
    return stringProcesado;
}


