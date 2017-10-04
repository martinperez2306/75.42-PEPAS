#include "../../headers/Model/servidor.h"
#include "../../headers/Model/logger.h"

#define LOGIN 1
#define BROADCAST 2
#define BUZON 3
#define LOGOUT 5
#define USER_DISCONNECT 6
#define RECONETION_FAIL 8

typedef pair<int, Socket*> socketConect;
typedef pair<int,int> mapPortFd;
typedef pair<int, string> usuarioConect;


std::list<int> crearPuertos(){
	
	std::list<int> puertos;
	for(int i = 8000; i <= 8007; i++)
		puertos.push_back(i);

	return puertos;
	
}

Servidor::Servidor(){
    loggear ("Entro al constructor del Servidor",2);
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
    this->mapUsuario = new map<int,string>();
    loggear ("Salio del constructor del Servidor",2);
    loggear (" ",2);

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
    loggear ("Entro al iniciar Servidor",2);
	/*Aqui se crea el socket escucha del servidor el cual es leido del XML*/
    
    loggear ("Crea el socket",2);
    asignarSocketEscucha(obtenerSocket()->Crear());
    string msg = "El puerto del servidor es: " + to_string(this->getPuerto());
    loggear (msg,3);
    obtenerSocket()->Enlazar(this->getPuerto());
    loggear ("Salgo del iniciar Servidor",2);
    loggear (" ",2);
   	
}

Socket* Servidor::iniciarConexion(int puerto) {
	Socket* newSocket= new Socket();
    string msg = "El puerto del cliente es: " + to_string(puerto);
    loggear (msg, 1);
    newSocket->Crear();

        while(!newSocket->Enlazar(puerto)){
            puerto++;
        }
    newSocket->Escuchar(this->getCantidadMaximaDeConexiones());
    int fd = newSocket->AceptarConexion();
    mapFD.insert(mapPortFd(fd,puerto));
    /*Agrego a la lista el puerto que estoy usando*/
    puertosEnUso.push_back(puerto);
    /*Piso el valor del fd por el nuevo que contiene la conexion aceptada*/
	newSocket->asignarFD(fd);
    loggear ("Conexion aceptada", 1);
    return newSocket;
}



Socket*  Servidor::aceptarConexiones() {
    loggear ("Entro al aceptarConexiones",2);
    /*Servidor recibe conexion de los clientes en el puerto de escucha*/
    loggear ("Escuchando conexiones",2);
    obtenerSocket()->Escuchar(this->obtenerSocketEscucha(),this->getCantidadMaximaDeConexiones());
    int fd = obtenerSocket()->AceptarConexion();
    string msg = "Conexion aceptada con fd: " + to_string(fd);
    loggear (msg , 3);
    loggear ("Asigno fd a socket",3);
    this->asignarSocketFD(fd);
    this->obtenerSocket()->asignarFD(fd);
    /*Valida que no se haya llegado al maximo de conexiones*/
    loggear ("Chequeo maximas conexiones",2);
    if(this->conexiones == this->cantidadMaximaDeConexiones){
        msg = "El servidor ha llegado a su maxima capacidad de conexiones.";
        loggear (msg,2);
        msg = "Cierro conexion con el socketFD: " + to_string(fd);
        loggear (msg,3);
        this->obtenerSocket()->CerrarConexion(fd);
        loggear ("Recupero el fd del socket que escucha",3);
        this->obtenerSocket()->asignarFD(this->obtenerSocketEscucha());
        loggear ("Salgo del aceptarConexiones",2);
        loggear (" ",2);

        return NULL;
    }else{
        loggear ("El servidor tiene conexiones disponibles",2);
        /*Toma un puerto de los disponibles*/
        int puerto = 8000;
        
        /*Lo quita de la pila*/
        /*Envia un mensaje al cliente con el nuevo puerto al que se debe conectar*/
        loggear ("Creo socket para la reconexion",2);
        Socket* newSocket= new Socket();
        newSocket->Crear();

        loggear ("Busco puertos no usados para enlazar",2);
        while(!newSocket->Enlazar(puerto)){
            msg = "Puerto usado: " + to_string(puerto);
            loggear(msg,3);
            puerto++;
        }
        string msg = "Conexion nueva en puerto: " + to_string(puerto);
        loggear(msg,3);
        cout<<msg<<endl;
        loggear("Le aviso al cliente el puerto al cual reconectarse",2);
        this->enviarMensaje(to_string(puerto), this->obtenerSocket());

        loggear("Escucho en el nuevo puerto",2);
        newSocket->Escuchar(this->getCantidadMaximaDeConexiones());
        loggear("AceptoConexion",2);
        int fdd = newSocket->AceptarConexion();
        msg = "Meto el fd y el puerto del nuevo socket en el map(FD = " + to_string(fdd) + " , puerto = " + to_string(puerto) + " )";
        loggear(msg,3);
        mapFD.insert(mapPortFd(fdd,puerto));
        /*Agrego a la lista el puerto que estoy usando*/
        msg = "Pusheo a la lista de puertos en uso el puerto: " + to_string(puerto);
        loggear(msg,3);
        puertosEnUso.push_back(puerto);
        /*Piso el valor del fd por el nuevo que contiene la conexion aceptada*/
        msg = "Asigno el nuevo fd al socket:" + to_string(fdd);
        loggear(msg,3);
        newSocket->asignarFD(fdd);
        
        /*Cierro la conexion con el socket escucha*/
        loggear ("Cierro la conexion con el fd viejo(el de escucha)", 2);
        obtenerSocket()->CerrarConexion(fd);
        loggear ("Reasigno el fd del socket escucha", 2);
        this->obtenerSocket()->asignarFD(this->obtenerSocketEscucha());
        /*Agregamos el socket del cliente y el servidor donde se comunicaran a la lista*/
        msg = "Meto el puerto y el  nuevo socket en el map(puerto = " + to_string(puerto) + " , socket)";
        loggear(msg,3);
        this->mapaSocket->insert(socketConect(puerto,newSocket));
        loggear("Aumento la cantidad de conexiones actuales",2);

        this->conexiones += 1;
        msg = "Cantidad de conexiones actuales: " + to_string(this->conexiones);
        loggear(msg,3);
        loggear("Conexion exitosa",2);
        loggear("Salgo del aceptarConexiones",2);
        loggear (" ",2);
        return newSocket;
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
    loggear("Entro al recibirMensaje",2);
    string msg;
    int largo = stoi(socket->Recibir(4), nullptr, 10);
    msg = "El largo del string recibido sera: " + to_string(largo);
    loggear(msg,3);
    loggear("Salio del recibirMensaje",2);
    loggear(" ",2);
	return socket->Recibir(largo);
}

void Servidor::enviarMensaje(string  mensa, Socket* socket){
    loggear("Entro al enviarMensaje",2);
    const void *mensaje = mensa.c_str();
    string msgLogger = "Mensaje enviado: " + mensa;
    loggear (msgLogger,2);
    socket->Enviar(mensaje, mensa.length());
    loggear("Salio del enviarMensaje",2);
    loggear(" ",2);
}


string Servidor::parsearMensaje(std::string datos, Socket* socketDelemisor){

	int i = 0;
	loggear("Entro al parsear mensaje",2);
	loggear ("El string recibido fue: " + datos,3);
	int codigo = stoi(obtenerParametros(datos,&i),nullptr,10);
	loggear("Paso el stoi tragico",3 );
	std::string usuario = obtenerParametros(datos,&i);
    string mensajeAEnviar;

	switch(codigo){
		case LOGIN:{
            loggear("Codigo de login",2);
			std::string password = obtenerParametros(datos,&i);
            mensajeAEnviar = validarCliente(usuario, password, socketDelemisor);
            enviarMensaje(mensajeAEnviar, socketDelemisor);
		}
			break;
		case BROADCAST:{
            loggear("Codigo de broadcast",2);
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
            loggear("Codigo de buzon",2);
            string msg;
			std::string destinatario = obtenerParametros(datos,&i);
			std::string mensaje = obtenerParametros(datos,&i);
            Usuario *usuarioDestinatario = this->obtenerBaseDeDatos()->getUsuario(destinatario);
            Usuario *usuarioEstaConectado = this->obtenerBaseDeDatos()->getUsuarioConectado(destinatario);
            loggear("Chequeo si existe el usuario al que se le manda el buzon",2);
            if (usuarioDestinatario == NULL || usuarioEstaConectado == NULL) {
                msg = "/4/El destinatario no existe o no se encuentra conectado.";
                loggear(msg,2);
                unsigned long largoDelMensaje = msg.length();
                string stringProcesado = this->agregarPadding(largoDelMensaje) + msg;
                this->enviarMensaje(stringProcesado, this->obtenerBaseDeDatos()->getUsuario(usuario)->getSocket());
            }else{
                loggear("El usuario existe",2);
                unsigned long largoDelMensaje = datos.length();
                string stringProcesado = this->agregarPadding(largoDelMensaje) + datos;
                loggear (stringProcesado,1);
                this->enviarMensaje(stringProcesado,usuarioDestinatario->getSocket());
            }
            break;
		}
        case LOGOUT:{
            loggear("Codigo de logout",2);
            string msg = "El usuario se ha deslogueado correctamente";
            loggear(msg,2);
            msg = procesarMensaje(msg);
            this->enviarMensaje(msg,socketDelemisor);
            this->desloguearse(usuario,socketDelemisor);

        }
			break;
        case USER_DISCONNECT:{
            loggear("Codigo de desconexion",2);
            loggear("Se desconecto el usuario con el FD: " + usuario,3);

            int fileD = stoi (usuario, nullptr,10);
            /*Obtengo el puerto a partir del FD*/
            //int puerto = mapFD.find(fileD)->first;
            int puerto = this->mapFD.find(fileD)->second;
            string msg = "Obtengo el par (FD = " + usuario + " , puerto = " + to_string(puerto) + " )";
            loggear(msg,3);
            loggear("Chequeo si el usuario que se desconecto estaba logueado",2);
            if(this->mapUsuario->count(puerto) > 0){
                loggear("Estaba logueado",3);
                this->desloguearse(this->mapUsuario->find(puerto)->second,socketDelemisor);
            }
            /*Cierro el socket*/
            loggear("Cierro conexion con el socket",2);
            this->mapaSocket->find(puerto)->second->CerrarConexion(fileD);
            loggear("Lo saco del map",2);
            std::map<int,Socket*>::iterator it;
            it = this->mapaSocket->find(puerto);
            mapaSocket->erase(it);
           /*Saco el puerto de uso*/
            auto iter = std::find (puertosEnUso.begin(), puertosEnUso.end(), puerto);

            /* Lo saco de la pila*/
            puertosEnUso.erase(iter);
            /*Lo pongo al principio de puertosDisponibles*/
            //puertosDisponibles.push_front(puerto);
            loggear("Disminuyo las conexiones actuales",2);
            this->conexiones -= 1;
            msg = "Conexiones actuales: " + to_string(this->conexiones);
            loggear(msg,3);
            mensajeAEnviar = "CerrarCliente";

        }
            break;
		default:
			break;
	}
    loggear("Salgo del parsearMensaje",2);
    loggear("",2);
return mensajeAEnviar;
}


void Servidor::desloguearse(string usuario,Socket* socketDelemisor){

    
    loggear("Saco al usuario de la base de datos",2);
    Usuario * usuarioLogOut = this->obtenerBaseDeDatos()->getUsuario(usuario);
    usuarioLogOut->estaDesconectado();
    this->obtenerBaseDeDatos()->sacarUsuarioConectadoABaseDeDatos(usuario);
    string msgLogger = "Usuario " + usuario + "desconectado";
    loggear (msgLogger,3);
    
}

string Servidor::validarCliente(string usuario, string contrasenia, Socket* socketDelEmisor) {
    loggear("Entro al validar cliente",2);
    Usuario *usuarioAValidar = this->obtenerBaseDeDatos()->getUsuario(usuario);
    string msg, msgOK, msgAdevolver;
    bool fallo = false;
    loggear("Chequeo el usuario",2);
    if (usuarioAValidar == NULL) {
        msg = "No existe el usuario ingresado";
        loggear(msg, 2);
        msg = procesarMensaje(msg);
        fallo = true;
    } else if(usuarioAValidar->getContrasenia() != contrasenia ||
            usuarioAValidar->getUsuario() != usuario) {
            msg = "Usuario o contraseña incorrectas";
            loggear(msg, 2);
            msg = procesarMensaje(msg);
            fallo = true;
        } else if (usuarioAValidar->getConectado()) {
                msg = "El usuario ingresado ya se encuentra conectado";
                loggear(msg, 2);
                msg = procesarMensaje(msg);
                fallo = true;
            } else {
                msgOK = "Bienvenido\n";
                loggear(msgOK, 2);
                msgOK = procesarMensaje(msgOK);
                usuarioAValidar->estaConectado();
                usuarioAValidar->asignarSocket(socketDelEmisor);
                this->baseDeDatos->agregarUsuarioConectadoABaseDeDatos(usuario);
                int puerto = this->mapFD.find(socketDelEmisor->obtenerFD())->second;
                this->mapUsuario->insert(usuarioConect(puerto,usuario));
            }

    msgAdevolver = msgOK;
    if (fallo){
        msgAdevolver = msg;
    }
loggear("Salio del validar cliente",2);
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
        auto got = mapaSocket->find(puertoActual);
        this->obtenerSocket()->CerrarConexion(got->second->obtenerFD());
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


