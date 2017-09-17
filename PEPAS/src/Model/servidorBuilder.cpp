#include "../../headers/Model/servidorBuilder.h"


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

	this->servidor->setCantidadDeConexiones(this->getCantidadDeConexiones());
	this->servidor->setPuerto(this->getPuerto());
	this->servidor->setBaseDeDatos(this->baseDeDatos);

	return this->getServidor();
}

void ServidorBuilder::parsearXML(){

	pugi::xml_document documento;
	pugi::xml_parse_result result = documento.load_file("src/server.xml");
	//pugi::xml_parse_result result = documento.load_file("../75.42-PEPAS/PEPAS/src/server.xml");
	cout << "Load Result: " << result.description() <<endl;

	//PARSING XML (EL COMPILADOR PODRIA DECIR QUE NO ANDA PERO SI ANDA WACHOS)
	pugi::xml_node nodePuerto = documento.child("servidor").child("puerto");
	int puerto = nodePuerto.text().as_int();
	pugi::xml_node nodeMaxClient = documento.child("servidor").child("cantidadMaximaClientes");
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
}

ServidorBuilder::~ServidorBuilder(){

}
