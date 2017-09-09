#include "../headers/Model/baseDeDatos.h"

class BaseDeDatosTest{

private:
	BaseDeDatos* baseDeDatos;

public:

	BaseDeDatosTest(){
		this->baseDeDatos = new BaseDeDatos();
	}

	void agregarUnUsuario(string username, string password){

		Usuario* usuario1 = new Usuario(username,password);
		this->baseDeDatos->agregarUsuarioABaseDeDatos(usuario1);
		this->baseDeDatos->mostrarTodosLosUsuarios();
	}

	void obtenerUnUsuario(string usuario){
		Usuario* usuario2 = new Usuario(usuario,"contraseña");
		this->baseDeDatos->agregarUsuarioABaseDeDatos(usuario2);
		this->baseDeDatos->mostrarTodosLosUsuarios();
		cout << this->baseDeDatos->getUsuario(usuario)->getUsuario()<<endl;
		cout << this->baseDeDatos->getUsuario(usuario)->getContrasenia()<<endl;
	}
	~BaseDeDatosTest(){
		delete baseDeDatos;
	}
};




