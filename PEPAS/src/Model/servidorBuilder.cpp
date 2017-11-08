#include "../../headers/Model/servidorBuilder.h"
#include "../../headers/Model/logger.h"


//SERVIDOR BUILDER

//BASE DE DATOS Y SERVIDOR SON PEDIDOS EN MEMORIA ACA. DEBEN SER LIBERADAS EN EL CONTROLLER (EL SERVIDOR) Y LA BASE DE DATOS (POR EL SERVIDOR)
ServidorBuilder::ServidorBuilder(){

	this->puerto = 0;
	this->cantidadDeConexiones = 0;
	this->servidor = new Servidor();
	this->baseDeDatos = new BaseDeDatos();
}


Servidor* ServidorBuilder::getServidor(){
	return this->servidor;
}

void ServidorBuilder::setServidor(Servidor* servidor){

	this->servidor = servidor;
}

int ServidorBuilder::getPuerto(){
	return this->puerto;
}

int ServidorBuilder::getCantidadDeConexiones(){
	return this->cantidadDeConexiones;
}

void ServidorBuilder::setCantidadDeConexiones(int cantidadDeConexiones){

	this->cantidadDeConexiones = cantidadDeConexiones;
}

void ServidorBuilder::setPuerto(int puerto){

	this->puerto = puerto;
}

Servidor* ServidorBuilder::build(){

	this->servidor->setCantidadMaximaDeConexiones(this->getCantidadDeConexiones());
	this->servidor->setPuerto(this->getPuerto());
	this->servidor->setBaseDeDatos(this->baseDeDatos);
	this->servidor->setZoomEntreMapaYMinimapa(10);
	this->servidor->generarMapa();
	this->servidor->generarMinimapa();
	this->servidor->generarWorld();
	return this->getServidor();
}

void ServidorBuilder::parsearXML(const char* archivo){

	pugi::xml_document documento;
	//pugi::xml_parse_result result = documento.load_file("src/server.xml");
	pugi::xml_parse_result result = documento.load_file(archivo);
	cout << "Load Result: " << result.description() <<endl;
	if (result.status ==0){
		//PARSING XML (EL COMPILADOR PODRIA DECIR QUE NO ANDA PERO SI ANDA WACHOS)
		pugi::xml_node nodePuerto = documento.child("servidor").child("puerto");

		if( puertoValido(nodePuerto.text().as_string())){

			int puerto = nodePuerto.text().as_int();
			pugi::xml_node nodeMaxClient = documento.child("servidor").child("cantidadMaximaClientes");


			if(sonDigitos(nodeMaxClient.text().as_string())){
				int maximoClientes = nodeMaxClient.text().as_int();
				cout<< puerto << endl;
				cout<< maximoClientes << endl;

				//SET USERS TO DATA BASE
				pugi::xml_node nodeUsers = documento.child("servidor").child("usuarios");

				for (pugi::xml_node nodeUser = nodeUsers.first_child(); nodeUser; nodeUser = nodeUser.next_sibling())  {

					// SE CREA UN USUARIO. BORRARLO CUANDO MATAMOS LA BASE DE DATOS.
					Usuario* usuario = new Usuario();
					for(pugi::xml_node userFeature = nodeUser.first_child();userFeature;userFeature = userFeature.next_sibling()){

						if((strcmp(userFeature.name(),"username")) == 0){
							usuario->setUsuario(userFeature.text().as_string());
						}
						if((strcmp(userFeature.name(),"password"))== 0){
							usuario->setContrasenia(userFeature.text().as_string());
						}

						this->baseDeDatos->agregarUsuarioABaseDeDatos(usuario);
				     }
					this->baseDeDatos->agregarUsuarioABaseDeDatos(usuario);
				}
				//BUILDING SERVICE FEATURES
				this->cantidadDeConexiones = maximoClientes;
				this->puerto = puerto;
			}else{
				cout << "Error al parsear la maxima cantidad de clientes, cargo default" << endl;

				this->parsearXML("serverDefault.xml");
			}
		}else{
			cout << "Error al parsear el puerto, cargo default" << endl;
			this->parsearXML("serverDefault.xml");
		}
	}else{
		this->parsearXML("serverDefault.xml");
	}
}


bool ServidorBuilder::puertoValido(const char* puertoTxt) {
	if(sonDigitos(puertoTxt)) {
		int puerto = atoi(puertoTxt);
		return puerto > 0 && puerto < 65535;
	} else {
		loggear("Puerto invalido parseado",3);
		return false;
	}
}

bool ServidorBuilder::sonDigitos(const char* str){
	for (unsigned int i = 0; i < strlen (str); i++) {
		if (! isdigit (str[i])) {
			loggear("No es un numero",3);
			return false;
		}
	}
	return true;
}

ServidorBuilder::~ServidorBuilder(){

}
