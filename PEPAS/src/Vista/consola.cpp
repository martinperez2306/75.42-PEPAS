#include "../../headers/Vista/consola.h"
#include "../../headers/Model/usuario.h"
#include "../../headers/Model/logger.h"
#include <string>

Consola::Consola(){

	this->terminado = false;
	//this->numeroPagina = 0;
	this->servidorController = new ServidorController();
}

bool Consola::getTerminado(){

	return this->terminado;
}

void Consola::cargarPagina(int numeroPagina){
	switch(numeroPagina){
		case 1:
			this->cargarPaginaCaracteristicasDelServidor();
			break;
		case 3:
		{
			this->terminarConsola();
			break;
		}
		case 2:
			this->cargarCambioLoggeo();
		default:
		{
			cout << "No existe esa opcion" << endl;
      		loggear("No existe el comando ingresado por consola",2);
			this->cargarPaginaPrincipal();
		}
	}
}

void Consola::cargarCambioLoggeo(){
	
	std::string nivel;
	cout << "Ingrese ERROR,ACTIVIDAD o DEBUG para indicar nivel de loggeo"<<endl;
	cin >> nivel;


	int i = 0;
   while (nivel[i] != '\0'){
      nivel[i] = tolower(nivel[i]);
      i++;
   }

   if(nivel.compare("error")==0)
   		setNivelLogger(1);
   else if (nivel.compare("actividad")==0)
   		setNivelLogger(2);
   else if(nivel.compare("debug")==0)
   		setNivelLogger(3);
   else 
   {
     	cout << "Opcion invalida" << endl;
      	loggear("Opcion invalida ingresada para el cambio del logger",2);
   } 


}
void Consola::cargarPaginaPrincipal(){

	std::string entrada;

	cout<<"Ingrese una opcion segun corresponda"<<endl;
	cout<<"Seleccione 1 para ir a las caracteristicas del servidor"<<endl;
	cout<<"Seleccione 2 para cambiar el nivel del logger"<<endl;
	cout<<"Seleccione 3 para salir"<<endl;
	
	cin>> entrada;

	if(esint(entrada)){
		int ent = std::stoi(entrada,nullptr,10);
		this->cargarPagina(ent);
	}
	else{

		cout << "Entrada invalida, debe ser un numero"<<endl;
      	loggear("Opcion invalida ingresada, no se ingreso un numero",2);
		this->cargarPaginaPrincipal();
	}
}

void Consola::cargarPaginaCaracteristicasDelServidor(){

	loggear("Cargado pagina con caracteristicas del servidor",3);
	Usuario* usuario = this->servidorController->getUsuario();

	cout<<"La cantidad maxima de conexiones es: "<<this->servidorController->getMaximoClientesServidor()<<endl;
	cout<<"El puerto es: "<<servidorController->getPuertoServidor()<<endl;
	cout<<"Usuario Disponible = "<<usuario->getUsuario()<<" "<<"Contrase�a = "<<usuario->getContrasenia()<<endl;
}

void Consola::cargarPaginaCrearServidor(){


	cout<<"CREANDO SERVIDOR..............."<<endl;
	loggear("Servidor Creado",3);
	this->servidorController->crearServidor();
	for(int i = 0;i<10;i++){
		cout<<"."<<endl;
	}
	cout<<"SERVIDOR CREADO CORRECTAMENTE"<<endl;
}



Consola::~Consola(){

	delete this->servidorController;
}


bool Consola::esint(std::string entrada){

	if (entrada.length() == 1 && isdigit(entrada[0]))
		return true;
	return false;
}

void Consola::terminarConsola(){
	this->terminado = true;
}