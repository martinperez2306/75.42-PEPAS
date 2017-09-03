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
	pugi::xml_parse_result result = documento.load_file("/home/payas17/CLionProjects/75.42-PEPAS/PEPAS/src/server.xml");
	cout << "Load Result: " << result.description() <<endl;
	/*pugi::xml_node panels = documento.child("servidor");

	    std::cout << panels.name() << std::endl;

	    for (pugi::xml_node panel = panels.first_child(); panel; panel = panel.next_sibling())
	    {
	        std::cout << panel.name() << std::endl;

	        for (pugi::xml_attribute attr = panel.first_attribute(); attr; attr = attr.next_attribute())
	        {
	            std::cout << " " << attr.name() << "=" << attr.value() << std::endl;
	        }
	        std::cout << std::endl;
	    }
	    std::cout << std::endl;*/

	//PARSING XML (EL COMPILADOR PODRIA DECIR QUE NO ANDA PERO SI ANDA WACHOS)
	pugi::xml_node nodePuerto = documento.child("servidor").child("puerto");
	int puerto = nodePuerto.text().as_int();
	pugi::xml_node nodeMaxClient = documento.child("servidor").child("cantidadMaximaClientes");
	int maximoClientes = nodeMaxClient.text().as_int();
	cout<< puerto << endl;
	cout<< maximoClientes << endl;

	pugi::xml_node nodeUser = documento.child("servidor").child("usuarios");
	string usuario = nodeUser.child("user").text().as_string();
	string contrasenia = nodeUser.child("password").text().as_string();

	//BUILDING SERVICE
	this->cantidadDeConexiones = maximoClientes;
	this->puerto = puerto;
	Usuario* user = new Usuario();
	user->setUsuario(usuario);
	user->setContrasenia(contrasenia);
	this->baseDeDatos->setUsuario(user);
}

ServidorBuilder::~ServidorBuilder(){

}
