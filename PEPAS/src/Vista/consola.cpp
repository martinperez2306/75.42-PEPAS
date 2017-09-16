#include "../../headers/Vista/consola.h"
#include "../../headers/Model/usuario.h"
#include "../../headers/Model/logger.h"
#include <string>

Consola::Consola(){

	this->terminado = false;
	this->servidorController = new ServidorController();
}

bool Consola::getTerminado(){
	return this->terminado;
}

void Consola::cargarPagina(int numeroPagina){
	//system("clear");
	switch(numeroPagina){
		case 1:
			this->cargarPaginaCaracteristicasDelServidor();
			break;
		case 2:
			this->servidorController->iniciarEscuchasDeConexiones();
			break;
		case 5:
		{
			this->terminarConsola();
			break;
		}
		case 3:
			this->cargarCambioLoggeo();
			break;
		case 4:
			this->servidorController->mostrarUsuariosConectados();
			break;
		default:
		{
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
	cout<<"****************************************************************"<<endl;
	cout<<"Ingrese una opcion segun corresponda"<<endl;
	cout<<"Seleccione 1 para ir a las caracteristicas del servidor"<<endl;
	cout<<"Seleccione 2 para levantar conexiones de servidor"<<endl;
	cout<<"Seleccione 3 para cambiar el nivel del logger"<<endl;
	cout<<"Seleccione 4 para ver los usuarios conectados"<<endl;
	cout<<"Seleccione 5 para salir"<<endl;
	cout<<"****************************************************************"<<endl;
	cout<<"--->";
	cin>>entrada;

	if(esint(entrada) && std::stoi(entrada,nullptr,10)>0 && std::stoi(entrada,nullptr,10) < 6
			){
		int ent = std::stoi(entrada,nullptr,10);
		this->cargarPagina(ent);
	}
	else{

		cout << "Entrada invalida"<<endl;
      	loggear("Opcion invalida ingresada",2);
		this->cargarPaginaPrincipal();
	}
}

void Consola::cargarPaginaCaracteristicasDelServidor(){

	loggear("Cargado pagina con caracteristicas del servidor",3);

	cout<<"La cantidad maxima de conexiones es: "<<this->servidorController->getMaximoClientesServidor()<<endl;
	cout<<"El puerto es: "<<servidorController->getPuertoServidor()<<endl;
	cout<<"Usuarios Disponibles "<<endl;
	this->servidorController->mostrarUsuariosDisponibles();
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


bool Consola::esint(std::string entrada){

	if (entrada.length() == 1 && isdigit(entrada[0]))
		return true;
	return false;
}

void Consola::terminarConsola(){
	this->terminado = true;
}

Consola::~Consola(){

	delete this->servidorController;
}
