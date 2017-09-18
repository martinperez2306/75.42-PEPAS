#include "../../headers/Controller/servidorController.h"
#include "../../headers/Model/ShutdownThread.h"


ServidorController::ServidorController() {

	this->servidor = NULL;
	this->servidorBuilder = NULL;
}


//RESERVA Y LIBERA MEMORIA DEL SERVIDOR BUILDER. QUEDA USANDOSE LA MEMORIA PEDIDA PARA SERVIDOR (QUE PIDIO SERVIDOR BUILDER)
void ServidorController::crearServidor(){

	this->servidorBuilder = new ServidorBuilder();
	this->servidorBuilder->parsearXML();
	this->servidor = this->servidorBuilder->build();
	delete servidorBuilder;
}

void ServidorController::mostrarUsuariosDisponibles(){

	this->servidor->mostrarUsuariosDisponibles();
}
int ServidorController::getMaximoClientesServidor(){

	return this->servidor->getCantidadDeConexiones();
}

int ServidorController::getPuertoServidor(){

	return this->servidor->getPuerto();
}

Usuario* ServidorController::getUsuario(string username){
	return this->servidor->getBaseDeDatos()->getUsuario(username);
}

void ServidorController::mostrarUsuariosConectados(){
	this->servidor->mostrarUsuariosConectados();
}

ServidorController::~ServidorController(){
	delete this->servidor;
}


void ServidorController::abrirServidorAClientes() {
    bool cerrarServidor = false;

    this->servidor->iniciarServidor();

    ShutdownThread shutdownThread(cerrarServidor, this->servidor);
    shutdownThread.start();

    while (!cerrarServidor) {
         //saco los threads que ya no se usan
        for (auto it = clientThreads.begin(); it != clientThreads.end();
             ++it){
            if (it->esBorrable()){
                it->join();
                it = clientThreads.erase(it);
            }
        }

        clientThreads.emplace_back(this->servidor->aceptarConexiones(), this->servidor, cerrarServidor);
        clientThreads.back().start();


    }
}

