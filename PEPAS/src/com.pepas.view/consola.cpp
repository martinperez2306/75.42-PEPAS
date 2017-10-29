#include "../../headers/com.pepas.view/consola.h"


Consola::Consola(const char* archivo){
   this->clienteController = new ClienteController(archivo);
   terminado = false;
}


bool esint(std::string entrada){

	if (entrada.length() == 1 && isdigit(entrada[0]))
		return true;
	return false;
}

void Consola::cargarMenuPrincipal() {
	string entrada;
	int numeroPag;
	while(!terminado) {
		
		cout<<"*********************************************"<<endl;
		cout<<"Ingrese una opcion segun corresponda"<<endl;
		cout<<"Seleccione 1 conectarse al servidor"<<endl;
		cout<<"Seleccione 2 para loguearse"<<endl;
		cout<<"Seleccione 3 para entrar al Chat"<<endl;
		cout<<"Seleccione 4 para el enviar un mensaje privado"<<endl;
		cout<<"Seleccione 5 para el Stress Test"<<endl;
		cout<<"Seleccione 6 para el deslogearse"<<endl;
		cout<<"Seleccione 7 para ver su buzon"<<endl;
		cout<<"Seleccione 8 para desconectarse"<<endl;
		cout<<"Seleccione 9 para salir"<<endl;
		cout<<"*********************************************"<<endl;
		cin>> entrada;
		if(!esint(entrada)){
			cout<<"Entrada invalida"<<endl;
			continue;
		}
		numeroPag = stoi(entrada,nullptr,10);

		switch(numeroPag) {
			case 1:
			{
				this->clienteController->conectar();
			}
				break;
			case 2:
			{
				this->clienteController->logIn();
				
			}
				break;
			case 3:
                this->clienteController->entrarAlChat();
				break;
			case 4:
				this->clienteController->enviarMensajePrivado();
				break;
			case 5:
				this->clienteController->stressTest();
				break;
			case 6:
				this->clienteController->logOut();
				break;
			case 7:
				this->clienteController->verBuzon();
				break;
			case 8:
				this->clienteController->desconectarseDelServidor();	
			break;
			case 9:
				this->clienteController->desconectarseDelServidor();
				terminado = true;	
			break;
			default:
				cout << "Opcion incorrecta" << endl;
		};
	}
	cout<<"Se va a cerrar la conexion con el servidor..."<<endl;
	this->clienteController->salirDelPrograma();
	

}

void Consola::cargarPaginaCrearCliente(){

    cout<<"CREANDO CLIENTE..............."<<endl;

    for(int i = 0;i<10;i++){
        cout<<"."<<endl;
    }
    cout<<"CLIENTE CREADO CORRECTAMENTE"<<endl;
    //this->cargarPaginaCaracteristicasDelCliente();
}

Consola::~Consola(){

    delete this->clienteController;
}

bool Consola::terminoConsola(){
	return this->terminado;
}

ClienteController* Consola::getController(){
	return this->clienteController;
}
