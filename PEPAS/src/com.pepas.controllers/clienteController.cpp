//
// Created by florencia on 03/09/17.
//

#include <iomanip>
#include "../../headers/com.pepas.controllers/clienteController.h"

#include <zconf.h>

ClienteController::ClienteController(){
	//this->socketData = this->clienteParser->parsearXML("cliente.xml");
    this->socketData = this->clienteParser->parsearXML("../75.42-PEPAS/PEPAS/cliente.xml");
	this->cliente= new Cliente();
	this->threadRecibir = recvThread(cliente);
	this->reconexion = false;

}


ClienteController::ClienteController(ClienteParser *clientePaser) {
	this->clienteParser = clientePaser;

}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)


void ClienteController::conectar(){

	if(this->cliente->estaConectado()){
		cout<< "Usted ya esta conectado" <<endl;
		return;
	}
	
	//Esto es para cerrar el thread de la conexion anterior.
	if(reconexion){
		this->dejarRecibir();
	}
		
	if (this->conectarConElServidor() == -1) {
		cout<<"Ocurrio un error al intentar conectarse, intente nuevamente"<<endl;
	} else {
        cout<<"Haciendo cambio de puerto"<<endl;
		this->obtengoPuertoNuevoYHagoConectar();
		this->cliente->conectarse();
		this->empezarRecibir();
		this->reconexion = true;

	}
}

int ClienteController::conectarConElServidor(){
    return this->cliente->conectarseAlServidor(socketData.ip, socketData.puerto);
}



void ClienteController::desconectarseDelServidor(){
	if(!this->cliente->estaConectado()){
		cout << "Usted no esta conectado" << endl;
		return;
	}
	if (cliente->estalogueado()){
		this->logOut();
	}

	this->cliente->desconectarse();
	this->obtenerCliente()->obtenerSocket()->CerrarConexion(this->obtenerCliente()->obtenerSocketFD());
	reconexion = false;
	this->dejarRecibir();
	this->cliente->vaciarColaChat();
	this->cliente->vaciarColaBuzon();


	cout<< "Se ha desconectado" << endl;

}



void ClienteController::logOut() {
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para desloguearse"<< endl;
		return;
	}

	this->obtenerCliente()->desloguearse();
	string usuario = this->obtenerCliente()->obtenerUsuario()->getNombre();
	this->obtenerCliente()->enviarMensaje(this->obtenerCliente()->procesarMensaje(usuario));

}

void ClienteController::logIn() {
	if(!this->cliente->estaConectado()){
		cout<< "Debe conectarse para loguearse" <<endl;
		return;
	}

	if(cliente->estalogueado()){
        cout << "Usted ya esta logueado" << endl;
        return;
    }
	
	this->cliente->logIn();

	if (this->cliente->estalogueado()){
		this->empezarRecibir();
	}

}


void ClienteController::stressTest(){

	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para enviar un mensaje"<< endl;
		return;
	}

	string milisegundos, totalmili;
	cout<<"Ingrese cantidad de milisegundos entre mensajes: ";
	int mili, total;
	try {
		cin >> milisegundos;
		mili = stoi(milisegundos, nullptr,10);
		cout<<"Ingrese cantidad de milisegundos en total: ";
		cin>>totalmili;
		total = stoi(totalmili, nullptr,10);
	}catch (std::invalid_argument)
	{
		cout << "Ingrese unicamente un numero " <<'\n';
	}
	ifstream myReadFile;
	myReadFile.open("cliente_test_file");
	string stressMsg;
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			//myReadFile >> output;
			getline(myReadFile,stressMsg);
			myReadFile.ignore();
			cout<<stressMsg<<endl;
		}
	}
	myReadFile.close();

	int i=0;
	do{
		enviarBroadcast(stressMsg);
		i += mili;
		usleep(mili);
	} while (i != total);




}



void ClienteController::enviarMensajePrivado(){
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para enviar un mensaje"<< endl;
		return;
	}
	string texto, mensajeProcesado, destinatario, bug;
    cout<<this->obtenerCliente()->obtenerUsuario()->getNombre()<<" ingresa el mensaje: ";
	//TODO aca hay un bug que no lo entiendo, si no pongo las variables de esta forma anda mal.
	getline (cin,bug);
	getline(cin, texto);
	cout<<"Ingresa el ususario destino: ";
	cin >> destinatario;
	Mensaje *mensaje = new Mensaje(Mensaje::PRIVATE_MSG, texto, this->obtenerCliente()->obtenerUsuario()->getNombre(), destinatario);
	mensajeProcesado = this->obtenerCliente()->procesarMensaje(mensaje);
	this->obtenerCliente()->enviarMensaje(mensajeProcesado);


}

void ClienteController::salirDelPrograma() {
	cout<<"SALISTE"<<endl;
	
}

ClienteController::~ClienteController(){
    delete this->cliente;
}

Cliente *ClienteController::obtenerCliente() {
    return this->cliente;
}


void ClienteController::obtengoPuertoNuevoYHagoConectar() {
	/*Recibo 4 bytes en donde ya se que voy a recibir 4 bytes con el puerto nuevo*/
	string puerto = this->obtenerCliente()->obtenerSocket()->Recibir(this->obtenerCliente()->obtenerSocketFD(), 4);
	/*Cierro la conexion con el puerto del xml*/
    cout<<"El puerto recibido es: "<<puerto<<endl;
	this->obtenerCliente()->obtenerSocket()->CerrarConexion(this->obtenerCliente()->obtenerSocketFD());

	/*Seteo mi nuevo puerto*/
	this->socketData.puerto= stoi(puerto,nullptr,10);
	/*Me conecto al nuevo servidor*/
	this->obtenerCliente()->conectarseAlServidor(socketData.ip, socketData.puerto);
	cout<<"Conectado satisfactorio con puerto: "<<socketData.puerto<<endl;

}

void ClienteController::empezarRecibir(){
	this->threadRecibir.start();
}

void ClienteController::dejarRecibir(){
	this->threadRecibir.join();
}




int kbhit()
{
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
	select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &fds);
}


void ClienteController::entrarAlChat() {
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para enviar un mensaje"<< endl;
		return;
	}

	//system("clear");
	cout<<"Presione & para salir del chat"<<endl;
	string entrada("");
	cin.ignore();

	do{

		while (!this->obtenerCliente()->obtenerColaChat().empty()){
			if (kbhit()){
				break;
			}
			cout<<this->obtenerCliente()->obtenerColaChat().front()<<endl;
			this->obtenerCliente()->desencolarColaChat();
		}

		if (kbhit()){
			getline(cin,entrada);
			cout<<"\e[A";
			enviarBroadcast(entrada);
		}
	}while(entrada.compare("&\0") != 0 && cliente->estalogueado());
}





void ClienteController::verBuzon() {
	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para ver el buzon"<< endl;
		return;
	}

	this->obtenerCliente()->verBuzon();
}


void ClienteController::enviarBroadcast(string entrada) {

	if (!cliente->estalogueado()){
		cout<< "Debe loguearse para enviar un mensaje"<< endl;
		return;
	}
	string mensajeProcesado;
	string destinatario = "";
	Mensaje *mensaje = new Mensaje(Mensaje::BROADCAST_MSG, entrada, this->obtenerCliente()->obtenerUsuario()->getNombre(), destinatario);
	mensajeProcesado = this->obtenerCliente()->procesarMensaje(mensaje);
	this->obtenerCliente()->enviarMensaje(mensajeProcesado);

}

