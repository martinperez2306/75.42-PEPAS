#include <zconf.h>
#include <ctime>

#include "../../headers/Model/servidor.h"
#include "../../headers/Model/logger.h"

#define LOGIN 1
#define BROADCAST 2
#define BUZON 3
#define LOGOUT 5
#define USER_DISCONNECT 6
#define SIGNAL_CONNECT 7
#define COMANDO 10

#define CASE_UP_KD 20
#define CASE_LEFT_KD 21
#define CASE_RIGHT_KD 22
#define CASE_DOWN_KD 23
#define CASE_UP_KU 24
#define CASE_LEFT_KU 25
#define CASE_RIGHT_KU 26
#define CASE_DOWN_KU 27
#define LISTO 51
#define STOP 69
#define SEGL 50
#define HORIZONTE 400


using namespace std;

typedef pair<int, Socket*> socketConect;
typedef pair<int,int> mapPortFd;
typedef pair<int, string> usuarioConect;
typedef pair<string, Auto*> usuarioAuto;


std::list<int> crearPuertos(){

	std::list<int> puertos;
	for(int i = 8000; i <= 8007; i++)
		puertos.push_back(i);
	return puertos;
}

list<int> Servidor::cargarLista() {
    std::list<int> modelos;
    for(int i = 1; i <= 4; i++)
        modelos.push_back(i);
    return modelos;
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
    this->aliveCounter = 0;
	this->puertosDisponibles = crearPuertos();
    this->modeloDeAuto = cargarLista();
	this->terminado = false;
	this->mapaSocket = new map<int,Socket*>();
    this->mapUsuario = new map<int,string>();
    this->mapAutitos = new map<string,Auto*>();
    //Mapas generado por pista parser
    this->mapas = new map<int,Mapa*>();
    loggear ("Salio del constructor del Servidor",2);
    loggear (" ",2);
    this->pistaParser= new PistaParser();
    //Mapa generado por pista parser
    this->mapa = NULL;
    //Minimapa seteado por zoomer
    this->minimapa = new Minimapa();
    //World seteado por el zoomer
    this->world = new World();
    //zoomer
    this->zoomer = new Zoomer();
    //Recorredor para el radar
    this->recorredor = new Recorredor();
    this->time = "0:0";
    empezarJuego = false;
    player = 1;
    this->carreraTerminada = false;
    this->pistaActual = 0;
    jugadoresListos=0;
    listos = false;
    this->contadorCarrera = 0;
    this->carreraGlobalTerminada = false;
    this->mover = false;
    this->timerThread.start();
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
    int j=0;
	loggear("Entro al parsear mensaje",2);
	loggear ("El string recibido fue: " + datos,3);
	int codigo = stoi(obtenerParametros(datos,&i),nullptr,10);
	loggear("Paso el stoi tragico",3 );
	std::string usuario = obtenerParametros(datos,&i);
    string mensajeAEnviar;

	switch(codigo){
		case COMANDO: {
//				this->logicaJuego->setRuta(this->mapa->getRuta());
			}
			break;
		case LOGIN:{
            loggear("Codigo de login",2);
			std::string password = obtenerParametros(datos,&i);
            mensajeAEnviar = validarCliente(usuario, password, socketDelemisor);
            enviarMensaje(mensajeAEnviar, socketDelemisor);

            if(mensajeAEnviar == "0014/4/Bienvenido\n"){
                enviarMinimapaACliente(socketDelemisor);
                enviarMapaACliente(socketDelemisor);
                cout<<"cree un auto"<<endl;
                Auto* autito = new Auto(player);
                this->mapAutitos->insert(usuarioAuto(usuario,autito));
                player++;
            }
            if (this->baseDeDatos->obtenerMapUsuariosConectados()->size()==this->cantidadMaximaDeConexiones){
                empezarJuego = true;
                map<int,Socket*>::iterator iterador;
                int i=0;
                for (iterador = mapaSocket->begin(); iterador != mapaSocket->end(); ++iterador){
                    string mensajeFin= this->procesarMensajeFin(i);
                    this->enviarMensaje(mensajeFin,iterador->second);
                    i++;
                }
                player = 1;
            }
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
	case LISTO:{
		this->jugadoresListos++;
		cout<<"hola"<<endl;
		map<int,Socket*>::iterator iterador;
		if(this->jugadoresListos == this->cantidadMaximaDeConexiones){
			timerThread.temporizar();
            this->jugadoresListos = 0;
			while (!timerThread.getIncremento()){
//				for (iterador = mapaSocket->begin(); iterador != mapaSocket->end(); ++iterador){
//				    string mensaje= "0005/50/" + to_string(i);
//				    this->enviarMensaje(mensaje,iterador->second);
//				}
				//Espera al incremento del timer
			}
			for (iterador = mapaSocket->begin(); iterador != mapaSocket->end(); ++iterador){
				string mensaje= "0003/40";
				this->enviarMensaje(mensaje,iterador->second);
			}
			this->timerThread.cronometrar();
//			timerThread.reiniciar();
			this->mover = true;
		}

	}break;

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
                cout<<usuario<<endl;
                grisados.push_front(mapUsuario->find(puerto)->second);
                mapAutitos->erase(usuario); // mapUsuario->find(puerto)->second
                player--;
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
            loggear("Disminuyo las conexiones actuales",2);
            this->conexiones -= 1;
            msg = "Conexiones actuales: " + to_string(this->conexiones);
            loggear(msg,3);
            mensajeAEnviar = "CerrarCliente";
        }
            break;
        case SIGNAL_CONNECT:{
            this->aliveCounter += 1;
            string msgLog = "El contador es: " + to_string(aliveCounter);
            loggear(msgLog,3);
            loggear ("Cliente se encuentra conectado por red", 2);
            string msg = "0009" + datos;
            this->enviarMensaje(msg, socketDelemisor);
        }
        break;
        case CASE_UP_KD:{
            //Obtengo datos del mensaje
        	if(!mover){
        		break;
        	}
            int pos = stoi(obtenerParametros(datos,&i),nullptr,10);
            int curve = stoi(obtenerParametros(datos,&i),nullptr,10);
            //Busco auto en map
            map<string,Auto*>::iterator it = this->mapAutitos->find(usuario);
            it->second->moveUP_KD(pos, curve);
            //string msg = it->second->calculateMove(); //Calcula el movimiento del propio auto, NO de los demas.
            //this->enviarMensaje(msg, socketDelemisor);


        }break;
        case CASE_LEFT_KD:{
        	if(!mover){
        	        		break;
        	        	}
            int curve = stoi(obtenerParametros(datos,&i),nullptr,10);
            //Busco auto en map
            map<string,Auto*>::iterator it = this->mapAutitos->find(usuario);
            it->second->moveLeft_KD(curve);
            //string msg = it->second->calculateMove(); //Calcula el movimiento del propio auto, NO de los demas.
            //this->enviarMensaje(msg, socketDelemisor);

        }break;
        case CASE_RIGHT_KD:{
        	if(!mover){
        	        		break;
        	        	}
            int curve = stoi(obtenerParametros(datos,&i),nullptr,10);
            //Busco auto en map
            map<string,Auto*>::iterator it = this->mapAutitos->find(usuario);
            it->second->moveRight_KD(curve);
            //string msg =it->second->calculateMove(); //Calcula el movimiento del propio auto, NO de los demas.
            //this->enviarMensaje(msg, socketDelemisor);
        }break;
        case CASE_DOWN_KD:{
        	if(!mover){
        	        		break;
        	        	}
            //Obtengo datos del mensaje
            int pos = stoi(obtenerParametros(datos,&i),nullptr,10);
            int curve = stoi(obtenerParametros(datos,&i),nullptr,10);
            //Busco auto en map
            map<string,Auto*>::iterator it = this->mapAutitos->find(usuario);
            it->second->moveDown_KD(pos,curve);
            //string msg =it->second->calculateMove(); //Calcula el movimiento del propio auto, NO de los demas.
            //this->enviarMensaje(msg, socketDelemisor);
        }break;
        case CASE_UP_KU:{
        	if(!mover){
        	        		break;
        	        	}
            //Obtengo datos del mensaje
            int pos = stoi(obtenerParametros(datos,&i),nullptr,10);
            int curve = stoi(obtenerParametros(datos,&i),nullptr,10);
            //Busco auto en map
            map<string,Auto*>::iterator it = this->mapAutitos->find(usuario);
            it->second->moveUP_KU(pos,curve);
           // string msg =it->second->calculateMove(); //Calcula el movimiento del propio auto, NO de los demas.
            //this->enviarMensaje(msg, socketDelemisor);
        }break;
        case CASE_LEFT_KU:{
        	if(!mover){
        	        		break;
        	        	}
            int curve = stoi(obtenerParametros(datos,&i),nullptr,10);
            //Busco auto en map
            map<string,Auto*>::iterator it = this->mapAutitos->find(usuario);
            it->second->moveLeft_KU(curve);
            //string msg = it->second->calculateMove(); //Calcula el movimiento del propio auto, NO de los demas.
            //this->enviarMensaje(msg, socketDelemisor);
        }break;
        case CASE_RIGHT_KU:{
        	if(!mover){
        	        		break;
        	        	}
            int curve = stoi(obtenerParametros(datos,&i),nullptr,10);
            //Busco auto en map
            map<string,Auto*>::iterator it = this->mapAutitos->find(usuario);
            it->second->moveRight_KU(curve);
            //string msg = it->second->calculateMove(); //Calcula el movimiento del propio auto, NO de los demas.
            //this->enviarMensaje(msg, socketDelemisor);
        }break;
        case CASE_DOWN_KU:{
        	if(!mover){
        	        		break;
        	        	}
            //Obtengo datos del mensaje
            int pos = stoi(obtenerParametros(datos,&i),nullptr,10);
            int curve = stoi(obtenerParametros(datos,&i),nullptr,10);
            //Busco auto en map
            map<string,Auto*>::iterator it = this->mapAutitos->find(usuario);
            it->second->moveDown_KU(pos,curve);
            //string msg =it->second->calculateMove();
            //this->enviarMensaje(msg, socketDelemisor);
        }break;
		default:
			break;
	}
    loggear("Salgo del parsearMensaje",2);
    loggear("",2);
return mensajeAEnviar;
}

bool Servidor::estaListo(){
	return this->listos;
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

                /////////////////
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
//DEBE BORRAR TODOS SUS ATRIBUTOS DINAMICOS
//DEBE LIMPIAR TODA LA MEMORIA QUE USEN SUS ATRIBUTOS DINAMICOS
Servidor::~Servidor(){
	//this->finalizarConexiones();
	delete this->minimapa;
	delete this->mapa;
	delete this->baseDeDatos;
	this->mapaSocket->clear();
	delete this->mapaSocket;
	this->mapAutitos->clear();
	delete this->mapAutitos;
	this->mapUsuario->clear();
	delete this->mapUsuario;
	delete this->zoomer;
	delete this->world;
	delete this->recorredor;
	delete this->serverSocket;
}

void Servidor::cerrarSockets() {
    //*Recorro lista de puertos y hasheo el puerto con el socket*//*
    while (!puertosEnUso.empty()){
        int puertoActual = puertosEnUso.front();
        puertosEnUso.pop_front();
        auto got = mapaSocket->find(puertoActual);
        //this->obtenerSocket()->CerrarConexion(got->second->obtenerFD());
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

void Servidor::setZoomEntreMapaYMinimapa(int zoom){
	this->zoomer->setTamanioZoom(zoom);
}

void Servidor::generarMapas(){
    loggear("Creando pistas desde archivos de configuracion",1);
    (*this->mapas)[1] = this->pistaParser->parsearMapa("pista1.xml");
    (this->mapas->find(1)->second->mostrarSegmentos());
    (this->mapas->find(1)->second->mostrarObjetos());
    (*this->mapas)[2] = this->pistaParser->parsearMapa("pista2.xml");
    (this->mapas->find(2)->second->mostrarSegmentos());
    (this->mapas->find(2)->second->mostrarObjetos());
    (*this->mapas)[3] = this->pistaParser->parsearMapa("pista3.xml");
    (this->mapas->find(3)->second->mostrarSegmentos());
    (this->mapas->find(3)->second->mostrarObjetos());
    loggear("Pistas cargadas",1);
    delete this->pistaParser;
    loggear("Eliminando pista parser",1);
    this->pistaActual = 1;
    this->setMapa(1);
    this->generarMinimapa();
    this->generarWorld();
}

void Servidor::generarMinimapa(){
    this->zoomer->zoomMapToMinimap(this->mapa,this->minimapa,this->recorredor);
}

void Servidor::generarWorld(){
	this->zoomer->zoomMapToWorld(this->mapa,this->world);
}


void Servidor::enviarMinimapaACliente(Socket* socket){

    list<Segmento*>* pista = this->minimapa->getSegmentos();
    list<Objeto*>* objetos = this->minimapa->getObjetos();

    for(list<Segmento*>::iterator it = pista->begin(); it != pista->end();++it){
    	Segmento* seg = *it;
    	int X1= seg->getPosicionInicial()->getX();
    	int Y1 =seg->getPosicionInicial()->getY();
    	int X2= seg->getPosicionFinal()->getX();
    	int Y2= seg->getPosicionFinal()->getY();
    	string mensajeAEnviar= this->procesarMensajeRutaMinimapa(X1,Y1,X2,Y2);
        usleep(20);
    	this->enviarMensaje(mensajeAEnviar,socket);
    	}


    for (list<Objeto*>::iterator it = objetos->begin(); it != objetos->end(); ++it){
    	Objeto* obj = *it;
    	int tipoArbol = obj->getArbol();
    	int tipoCartel = obj->getCartel();
    	int distancia = obj->getDistancia();
    	string ladoDelObjeto = obj->getLado();
    	string mensajeAEnviar = this->procesarMensajeObjetoMinimapa(tipoArbol,tipoCartel,distancia,ladoDelObjeto);
        usleep(20);
    	this->enviarMensaje(mensajeAEnviar,socket);
    }
}

void Servidor::enviarMapaACliente(Socket* socketCliente){
	list<Segmento*>* ruta = this->mapa->getRuta();
	list<Objeto*>* objetos = this->mapa->getObjetos();

	for(list<Segmento*>::iterator it = ruta->begin(); it != ruta->end();++it){
	  	Segmento* seg = *it;
	  	int longitud = seg->getLongitud();
	  	int curva = seg->getCurva();
	   	string mensajeAEnviar= this->procesarMensajeRutaMapa(longitud,curva);
        usleep(200);
	   	this->enviarMensaje(mensajeAEnviar,socketCliente);
	}

	for (list<Objeto*>::iterator it = objetos->begin(); it != objetos->end(); ++it){
    	Objeto* obj = *it;
    	int tipoArbol = obj->getArbol();
    	int tipoCartel = obj->getCartel();
    	int distancia = obj->getDistancia();
    	string ladoDelObjeto = obj->getLado();
    	string mensajeAEnviar = this->procesarMensajeObjetoMapa(tipoArbol,tipoCartel,distancia,ladoDelObjeto);
        usleep(200);
    	this->enviarMensaje(mensajeAEnviar,socketCliente);
	}


}

void Servidor::enviarFinMapas(Socket* socketCliente, int i ){
	string mensajeFin= this->procesarMensajeFin(i);
   	this->enviarMensaje(mensajeFin,socketCliente);
}

/*Este procesador, codifica el mensaje con el codigo 9.
/<codigo_mensaje>/<arbol>/<cartel>/<distancia>/<lado>/*/
string Servidor::procesarMensajeObjetoMinimapa(int arbol, int cartel, int distancia, string lado){
	string stringACrear, stringProcesado;
	string separador = "/";
	string arb = to_string(arbol);
	string cart = to_string(cartel);
	string dist = to_string(distancia);
	stringACrear = separador + "9" + separador + arb + separador + cart + separador + dist + separador +lado;
	unsigned long largoDelMensaje = stringACrear.length();
	stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
	loggear(stringProcesado,1);
	return stringProcesado;
}

/*Este procesador, codifica el mensaje con el codigo 8.
<código_mensaje>/<X1>/<Y1>/<X2>/<Y2>/*/
string Servidor::procesarMensajeRutaMinimapa(int x1, int y1, int x2, int y2) {
    string stringACrear, stringProcesado;
    string separador = "/";
    string X1=to_string(x1);
    string X2=to_string(x2);
    string Y1=to_string(y1);
    string Y2=to_string(y2);
    stringACrear = separador + "8" + separador + X1 + separador + Y1 + separador + X2 + separador + Y2;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    loggear(stringProcesado,1);
    return stringProcesado;
}

/*Este procesador, codifica el mensaje con el codigo 11.
<código_mensaje>/<longitud>/<curva>/*/
string Servidor::procesarMensajeRutaMapa(int longitud, int curva){
	string stringACrear, stringProcesado;
	string separador = "/";
	string longit = to_string(longitud);
	string curv = to_string(curva);
	stringACrear = separador + "11" + separador + longit + separador +  curv;
	unsigned long largoDelMensaje = stringACrear.length();
	stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
	//loggear(stringProcesado,1);

	return stringProcesado;
}

/*Este procesador, codifica el mensaje con el codigo 12.
/<codigo_mensaje>/<arbol>/<cartel>/<distancia>/<lado>/*/
string Servidor::procesarMensajeObjetoMapa(int arbol, int cartel, int distancia, string lado){
	string stringACrear, stringProcesado;
	string separador = "/";
	string arb = to_string(arbol);
	string cart = to_string(cartel);
	string dist = to_string(distancia);
	stringACrear = separador + "12" + separador + arb + separador + cart + separador + dist + separador +lado;
	unsigned long largoDelMensaje = stringACrear.length();
	stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
	//loggear(stringProcesado,1);
	return stringProcesado;
}

/*Este procesador, codifica el mensaje con el codigo 10.
<código_mensaje>/*/

string Servidor::procesarMensajeFin(int i){
    string stringACrear,stringProcesado;
    string separador="/";

    auto model = modeloDeAuto.begin();
    advance(model, i);
    string modelCar = to_string(*model);

    cout<<"Model car: "<<modelCar<<endl;
    string cantJugadores = to_string(this->cantidadMaximaDeConexiones);
    stringACrear = separador + "10" + separador + modelCar +separador+ cantJugadores;
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    loggear(stringProcesado,1);
    return stringProcesado;
}

int Servidor::obtenerAlive() {
    return aliveCounter;
}

bool Servidor::getEmpezoJuego() {
    return empezarJuego;
}

void Servidor::setEmpezoJuego(bool entrada) {
    empezarJuego = entrada;
}

string Servidor::obtenerUsuarioConFd(int fd) {
    return mapUsuario->find(fd)->second;
}

Auto *Servidor::obtenerAutoConId(string id) {
    return this->mapAutitos->find(id)->second;
}

/*cantidadDeRivalesAGraficar/PosX/Horizonte ... eso para cara jugador*/
string Servidor::actualizarJuego(Auto *pAuto) {
    int i=0;
    string stringArmado = "";
    string stringConcat, stringAnterior, stringMinimapa,stringTime;
    string separador = "/";
    int horizonte = HORIZONTE;
    stringMinimapa = to_string(mapAutitos->size());
    stringTime = timerThread.getTiempo();
    bool salioDeColision;
    Auto * primero = NULL;
//    obtengoElPrimero(primero);

    int posYAux = 0;

    int posY = 0;
    bool primeraVez = true;
    for (std::map<string,Auto*>::iterator it = this->mapAutitos->begin(); it != this->mapAutitos->end(); ++it) {
        posY = it->second->getPosition()/SEGL;
        if(primeraVez) {
            posYAux = posY;
            primero = it->second;
            primeraVez = false;
        }
        if(posY > posYAux) {
            posYAux = posY;
            primero = it->second;
        }
    }

	for (std::map<string,Auto*>::iterator it = this->mapAutitos->begin(); it != this->mapAutitos->end(); ++it) {
		posY = it->second->getPosition()/SEGL;
		if(primeraVez) {
			posYAux = posY;
			primero = it->second;
			primeraVez = false;
		}
		if(posY > posYAux) {
			posYAux = posY;
			primero = it->second;
		}
	}


    for (std::map<string,Auto*>::iterator it=mapAutitos->begin(); it!=mapAutitos->end(); ++it){
        //cout<<"autitos size"<<mapAutitos->size()<<endl;
        stringConcat= "";
        Posicion* posicionDelAuto = NULL;

        posicionDelAuto = this->recorredor->getPosicionEnDistancia((int)it->second->getPosition()/2000);
        stringMinimapa = stringMinimapa + separador + to_string(it->second->obtenerPlayer()) + separador + to_string(posicionDelAuto->getX()) + separador + to_string(posicionDelAuto->getY());
        calcularPuntaje(it->second, primero);

        float diferenciaY = (it->second->getPosition()/SEGL) - (pAuto->getPosition()/SEGL);
        float diferenciaX = abs(pAuto->getX() - it->second->getX());
        if (diferenciaY <= horizonte && it->second != pAuto && abs(diferenciaY) >= 0) {
            if ( diferenciaX <= 185 && abs(diferenciaY) <= 4){
                pAuto->estaEnColision(pAuto->getLastMove(), pAuto->getVelY());
                if (salioDeColision){
                    pAuto->agregarDestrozo();
                    it->second->agregarDestrozo();
                    salioDeColision= false;
                }
            } else {
                // cout<<pAuto->getLastMove()<<endl;
                pAuto->noEstaEnColision();
                salioDeColision = true;
            }
            i++;
            if (i>=1) {
                stringConcat = to_string(it->second->obtenerPlayer()) + separador + to_string(it->second->obtenerDestrozo()) + separador +to_string(it->second->getX()) + separador + to_string(diferenciaY) + separador;
            } else stringConcat = to_string(it->second->obtenerPlayer())+ separador +to_string(it->second->obtenerDestrozo()) + separador+ to_string(it->second->getX()) + separador + to_string(diferenciaY);

        }
        stringArmado = stringArmado + stringConcat;
    }
    stringArmado = stringTime + separador + to_string(pAuto->obtenerDestrozo())+ separador+ stringMinimapa + separador+ to_string(i) + separador + stringArmado;
    if (i==0)
        stringArmado =  stringTime + separador +  to_string(pAuto->obtenerDestrozo()) + separador + stringMinimapa + separador +  to_string(0);
    return stringArmado;
}


void Servidor::obtengoElPrimero(Auto * primero) {
	int posYAux = 0;
	int posY = 0;
	cout << "voy a iterar entre los autos" << endl;
	bool primeraVez = true;
	for (std::map<string,Auto*>::iterator it = this->mapAutitos->begin(); it != this->mapAutitos->end(); ++it) {
		posY = it->second->getPosition()/SEGL;
		if(primeraVez) {
			posYAux = posY;
			primero = it->second;
			primeraVez = false;
		}
		if(posY > posYAux) {
			cout << "entro al if" << endl;
			posYAux = posY;
			primero = it->second;
		}
		cout << "salgo del if" << endl;
	}
	cout << "el primero es: " << primero->obtenerPlayer() << endl;
}

void Servidor::calcularPuntaje(Auto * autito, Auto * primero) {
	// si es el primero
	/*cout<<"ultposy: " << autito->getUltPosY() << endl;
	cout<<"posy: " << autito->getPosition()/SEGL << endl;*/
	if(autito->getPosition()/SEGL >= autito->getUltPosY() + 1) {
		if(autito->obtenerPlayer() == primero->obtenerPlayer()) {
			if(autito->getEtapa() == 1)
				autito->setScoreEtapa1( autito->getVelY() * 2 * 3.6 );
			else if(autito->getEtapa() == 2)
				autito->setScoreEtapa2( autito->getVelY() * 2 * 3.6 );
			else
				autito->setScoreEtapa3( autito->getVelY() * 2 * 3.6 );
		} else {
			if(autito->getEtapa() == 1)
				autito->setScoreEtapa1( autito->getVelY() * 3.6 );
			else if(autito->getEtapa() == 2)
				autito->setScoreEtapa2( autito->getVelY() * 3.6 );
			else
				autito->setScoreEtapa3( autito->getVelY() * 3.6);
		}
		/*cout<<"la velocidad es: " << autito->getVelY() << endl;
		cout<<"el puntaje es: " << autito->getScoreEtapa1() << endl;*/
		autito->setUltPosY(autito->getPosition()/SEGL);
	}

}


//Devuelve que tipo de curva es en cierto kilometraje
int Servidor::curvaEnKilometraje(int posicionY){
	return this->world->obtenerCurvaEnKilometraje(posicionY);
}

list<string> Servidor::obtenerGrisados() {
    return grisados;
}

bool Servidor::hayColision() {
    return colision;
}

void Servidor::setMapa(int numeroMapa){
    this->mapa = this->mapas->find(numeroMapa)->second;
}

string Servidor::renderTiempo(clock_t sTime) {
    int secondsPassed;
    int minutesPassed;
    secondsPassed =  ((clock() - sTime ) / (CLOCKS_PER_SEC));
    cout<<"seconds : "<< secondsPassed<<endl;
    minutesPassed = secondsPassed / 60;

    secondsPassed = secondsPassed - (minutesPassed * 60) ;

    string tiempo = to_string((int)minutesPassed) + ":" + to_string((int)secondsPassed);

    return tiempo;
}

void Servidor::setTime(string timeString) {
    this->time =timeString;

}



bool Servidor::actualizarEstadoDeCarrera(int posicionDeAuto, bool finish){
    if (this->world->carreraHaTerminado(posicionDeAuto) && !finish ){
        this->contadorCarrera = contadorCarrera + 1;
        finish = true;
    }
    if (contadorCarrera == this->cantidadMaximaDeConexiones) {
        this->carreraGlobalTerminada = true;
        cout<<"ARRE"<<endl;
        //this->contadorCarrera = 0;
    }

    return finish;
}

int Servidor::getContador(){
    return contadorCarrera;
}

bool Servidor::carreraHaTerminado(){
	return this->carreraTerminada;
}

void Servidor::cambiarDePista(){
	//limpiar los viejos mapas
	cout<<"Limpiando"<<endl;
	this->minimapa->limpiarMinimapa();
	this->world->limpiarWolrd();
	this->recorredor->limpiarRecorredor();
	//generar los nuevos mapas
	cout<<"Generando otra vez"<<endl;
	this->pistaActual = this->pistaActual + 1;
	this->setMapa(this->pistaActual);
	this->generarMinimapa();
	this->generarWorld();
	this->carreraTerminada = false;
    this->contadorCarrera = 0;
	//resetear los autos
	cout<<"Reseteando autos"<<endl;
	for(std::map<string,Auto*>::iterator it= this->mapAutitos->begin(); it!=this->mapAutitos->end();++it){
		Auto* automovil = it->second;
		automovil->setPosInicialDelAuto();
		automovil->incrementarEtapa();
		automovil->setUltPosY(0);
	}
	//enviar los nuevos mapas a los clientes
	cout<<"Enviando nueva info"<<endl;
    int i = 0;
	for (std::map<int,Socket*>::iterator it=this->mapaSocket->begin(); it!=this->mapaSocket->end(); ++it){
		this->enviarMinimapaACliente(it->second);
		this->enviarMapaACliente(it->second);
		this->enviarFinMapas(it->second, i);
        string mensaje= "0003/69";
        this->enviarMensaje(mensaje,it->second);
        cout<<"ENVIO MENSAJE DE STOP"<<endl;
        i++;
	}
//    timerThread.stop();
//    timerThread.join();

    this->carreraGlobalTerminada = false;
}

void Servidor::setPistaActual(int pistaActual){
	this->pistaActual = pistaActual;
}

int Servidor::getPistaActual(){
	return this->pistaActual;
}

string Servidor::procesarMensajeCambioDePista(){
    string stringACrear, stringProcesado;
    string separador = "/";
    stringACrear = separador + "30" + separador+ to_string(mapAutitos->size()) + separador + to_string(this->pistaActual);
    for (std::map<string,Auto*>::iterator it=this->mapAutitos->begin(); it!=this->mapAutitos->end(); ++it){
        string usuario = it->first;
        int total = (it->second->getScoreEtapa1()) + (it->second->getScoreEtapa2()) + (it->second->getScoreEtapa3());
        string totalEtapas = to_string(total);
        string scoreEtapa;
        switch (this->pistaActual){
            case 1:
                scoreEtapa = to_string(it->second->getScoreEtapa1());
                break;
            case 2:
                scoreEtapa = to_string(it->second->getScoreEtapa2());
                break;
            case 3:
                scoreEtapa = to_string(it->second->getScoreEtapa3());
                break;
        }
        stringACrear = stringACrear + separador + usuario + separador + scoreEtapa + separador+ totalEtapas;
    }
    unsigned long largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;

    return stringProcesado;
}

void Servidor::enviarMensajeCambioDePista(){
	string mensaje = this->procesarMensajeCambioDePista();
	for (std::map<int,Socket*>::iterator it=this->mapaSocket->begin(); it!=this->mapaSocket->end(); ++it){
		this->enviarMensaje(mensaje, it->second);
		cout<<"Envio cambio de pista"<<endl;
		cout<<mensaje<<endl;
	}
}

bool Servidor::carreraGlobalHaTerminado() {
    return this->carreraGlobalTerminada;
}

