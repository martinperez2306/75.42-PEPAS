#include "../../headers/com.pepas.model/cliente.h"
#include "../../headers/com.pepas.logger/Logger.h"

#define LOGIN 1
#define BROADCAST 2
#define BUZON 3

Cliente::Cliente() {
    this->socketCliente = new Socket();
    this->usuario = new Usuario();
    this->socketFD=0;
}

void Cliente::logIn(){
    string usuario;
    string clave;
    cout<<"Ingrese su nombre de usuario"<<endl;
    cin>> usuario;
    cout<<"Ingrese su clave"<<endl;
    cin>> clave;
    this->obtenerUsuario()->setearNombre(usuario);
    this->obtenerUsuario()->setearContrasenia(clave);
    this->validarUsuario(obtenerUsuario());
}

void Cliente::conectarseAlServidor(string ip, int puerto) {
    asignarSocketFd(obtenerSocket()->Crear());
    cout<<"Socket creado... Conectando..."<<endl;
    this->obtenerSocket()->Conectar(obtenerSocketFD(),puerto, ip); //TODO HARDCODEADO
    cout <<"Conectado satisfactorio"<< endl;

}


void Cliente::desconectarseDelServidor() {
    //neesito ver lo del servidor?
}


Cliente::~Cliente() {

}

void Cliente::asignarSocketFd(int socket) {
    this->socketFD=socket;

}

int Cliente::obtenerSocketFD() {
    return socketFD;
}

Socket* Cliente::obtenerSocket() {
        return this->socketCliente;

}

Usuario *Cliente::obtenerUsuario() {
    return this->usuario;
}

void Cliente::validarUsuario(Usuario* usuario) {

    //Codigo de mensaje 01
    string mensaje = this->procesarMensaje(usuario->getNombre(), usuario->getContrasenia());
    this->enviarMensaje(mensaje);
    cout<<"Mensaje enviado con exito"<<endl;
}
void Cliente::enviarMensaje(string  mensa){
    const void *mensaje = mensa.c_str();
    this->obtenerSocket()->Enviar(obtenerSocketFD(), mensaje, mensa.length());
}

std::string Cliente::recibirMensaje(){
	int largo = stoi(this->socketCliente->Recibir(this->socketFD, 4),nullptr,10);
	cout<<"paso el stoi"<<endl;
	return this->socketCliente->Recibir(this->socketFD, largo);
}
/*Este procesador, codifica el mensaje con el codigo 1.
<código_mensaje>/<usuario>/<password>*/

string Cliente::procesarMensaje(string usuario, string contrasenia) {
    string stringACrear, stringProcesado;
    string separador = "/";
    stringACrear = separador + "1" + separador + usuario + separador + contrasenia;
    int largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    cout<<stringProcesado<<endl;
    return stringProcesado;
}


/*Este procesador, codifica el mensaje con el codigo 2.
<código_mensaje>/<usuario>/<mensaje>

Este procesador, codifica el mensaje con el codigo 3
 <código_mensaje>/<usuario>/<destinatario>/<mensaje>*/
string Cliente::procesarMensaje(Mensaje *mensaje) {
    string stringACrear,stringProcesado;
    string separador = "/";
    if (mensaje->obtenerDestinatario()==""){
        stringACrear = to_string(mensaje->obtenerCodigo()) + separador + mensaje->obtenerEmisor() + separador + mensaje->obtenerTexto();
    } else {
        stringACrear = separador + to_string(mensaje->obtenerCodigo()) + separador + mensaje->obtenerEmisor() + separador + mensaje->obtenerDestinatario() + separador + mensaje->obtenerTexto();
    }
    int largoDelMensaje = stringACrear.length();
    stringProcesado = this->agregarPadding(largoDelMensaje) + stringACrear;
    cout<<stringProcesado<<endl;
    return stringProcesado;
}

string Cliente::agregarPadding(int lenght) {
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


std::string obtenerParametros(std::string mensaje, int* i){
	std::string aux = "";
	*i = *i + 1;
	while(mensaje[*i] != '/' && mensaje[*i] != '\0'){
		aux = aux + mensaje[*i];
		*i = *i + 1;
	}


	return aux;

}

void Cliente::parsearMensaje(std::string datos){

	int i = 0;
	loggear("entro al parsear mensaje",1);
	loggear (datos,1);
	int codigo = stoi(obtenerParametros(datos,&i),nullptr,10);
	loggear("paso el stoi tragico",1 );
	std::string usuario = obtenerParametros(datos,&i);

	switch(codigo){
		case LOGIN:{

			std::string password = obtenerParametros(datos,&i);
			cout << "Conectado correctamente con usuario ";
			cout << usuario + " " + password << endl;
		}

			break;
		case BROADCAST:{
			std::string mensaje = obtenerParametros(datos,&i);
		}
			break;
		case BUZON:{
			std::string destinatario = obtenerParametros(datos,&i);
			std::string mensaje = obtenerParametros(datos,&i);
		}
			break;
		default:
			break;
	}

}
