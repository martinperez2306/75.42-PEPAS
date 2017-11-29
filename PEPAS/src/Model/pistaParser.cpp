#include "../../headers/Model/pistaParser.h"

PistaParser::PistaParser(){
	this->puntero = new Puntero();
	this->posicionActual = NULL;
}

void PistaParser::setPosicionActual(Posicion* posActual){
	this->posicionActual = posActual;
}

Posicion* PistaParser::getPosicionActual(){
	return this->posicionActual;
}

int PistaParser::generarDireccion(string direccion){
	int angulo = -1;
	cout<<direccion<<endl;
	if(direccion.compare("este") == 0){
		angulo = 0;
	}
	if(direccion.compare("noreste") == 0){
		angulo = 45;
	}
	if(direccion.compare("norte") == 0){
		angulo = 90;
	}
	if(direccion.compare("noroeste") == 0){
		angulo = 135;
	}
	if(direccion.compare("oeste") == 0){
		angulo = 180;
	}
	if(direccion.compare("sudoeste") == 0){
		angulo = 225;
	}
	if(direccion.compare("sur") == 0){
		angulo = 270;
	}
	if(direccion.compare("sudeste") == 0){
		angulo = 315;
	}

	return angulo;
}

void PistaParser::girarYAvanzar(string direccion,int distancia,Mapa* mapa){

	Posicion* posicionAuxiliar = this->posicionActual;
	Posicion* posicionFinal = this->posicionActual;

	//evitar añadir un segmento de longitud 0 (caso de girar solamente)
	if(distancia != 0){
		Segmento* segm = new Segmento();

		if(direccion.compare("derecho") == 0){
			posicionFinal = this->puntero->avanzar(this->posicionActual,distancia);
			segm->setCurva(RECTO);
		}
		if(direccion.compare("derecha") == 0){
			this->puntero->girarDerecha();
			posicionFinal = this->puntero->avanzar(this->posicionActual,distancia);
			segm->setCurva(CURVAD);
		}
		if(direccion.compare("izquierda") == 0){
			this->puntero->girarIzquierda();
			posicionFinal = this->puntero->avanzar(this->posicionActual,distancia);
			segm->setCurva(CURVAI);
		}
		//ACA CREAMOS UN SUBSEGMENTO!!(OJO: CLASE SE LLAMA SEGMENTO PERO ES UN SUBSEGMENTO)
		segm->setLongitud(distancia);
		segm->setPosicionInicial(posicionAuxiliar);
		segm->setPosicionFinal(posicionFinal);
		mapa->agregarSegmento(segm);
		this->posicionActual = posicionFinal;
	}
	else{
		if(direccion.compare("derecha") == 0){
			this->puntero->girarDerecha();
		}
		if(direccion.compare("izquierda") == 0){
			this->puntero->girarIzquierda();
		}
	}
}

void PistaParser::generarObjeto(int distancia,string ladoDeLosObjetos,pugi::xml_node tipoDeObjeto,Mapa* mapa){

	Objeto* objeto = new Objeto();

	pugi::xml_node nodeType = tipoDeObjeto.first_child();

	//LADO DEL OBJETO
	if(ladoDeLosObjetos.compare("derecha") == 0){

		objeto->setLado("D");

		string obj = nodeType.name();

		//TIPO DE OBJETO
		if(obj.compare("arbol") == 0){
			objeto->setArbol(ARBOL);
		}
		if(obj.compare("cartel") == 0){
			int velocidadMaxima = nodeType.text().as_int();
			objeto->setCartel(velocidadMaxima);
		}
	}
	//LADO DEL OBJETO
	if(ladoDeLosObjetos.compare("izquierda")== 0){

		objeto->setLado("I");

		string obj = nodeType.name();

		//TIPO DE OBJETO
		if(obj.compare("arbol") == 0){
			objeto->setArbol(ARBOL);
		}
		if(obj.compare("cartel") == 0){
			int velocidadMaxima = nodeType.text().as_int();
			objeto->setCartel(velocidadMaxima);
		}
	}
	//DISTANCIA DEL OBJETO
	objeto->setDistancia(distancia);

	mapa->agregarObjeto(objeto);
}


Mapa* PistaParser::parsearMapa(const char* archivo){
	Mapa* mapa = new Mapa();
	pugi::xml_document documento;
	pugi::xml_parse_result result = documento.load_file(archivo);
	cout << "Load Result: " << result.description() <<endl;
	if (result.status ==0){
		//Si no hubo error parseamos el xml
		pugi::xml_node nodeInicio = documento.child("minimapa").child("inicio");
		pugi::xml_node inicioX = nodeInicio.child("x");
		pugi::xml_node inicioY = nodeInicio.child("y");

		this->posicionActual = new Posicion(inicioX.text().as_int(),inicioY.text().as_int());

		pugi::xml_node nodeInitialDir = documento.child("minimapa").child("direccionInicial");
		int direccionInicial = this->generarDireccion(nodeInitialDir.text().as_string());
		cout<<"direccionInicial "<<direccionInicial<<endl;
		this->puntero->setAngulo(direccionInicial);

		//Buscamos en todos los segmentos del xml
		pugi::xml_node nodeSegments = documento.child("minimapa").child("segmentos");
		//Detectamos la ruta y creamos los segmentos de ruta con sus correspondientes objetos
		pugi::xml_node nodeRoute = nodeSegments.child("ruta");
		for(pugi::xml_node nodeDirection = nodeRoute.first_child(); nodeDirection; nodeDirection = nodeDirection.next_sibling()){
			this->girarYAvanzar(nodeDirection.name(),nodeDirection.text().as_int(),mapa);
		}
		//Detectamos los objetos que contendra el segmento (arboles, carteles, etc)
		pugi::xml_node nodeObjects = nodeSegments.child("objetos");
		for(pugi::xml_node nodeObject = nodeObjects.first_child(); nodeObject;nodeObject = nodeObject.next_sibling()){
			pugi::xml_node nodeObjectDist = nodeObject.child("distancia");
			pugi::xml_node nodeObjectPos = nodeObject.child("posicion");
			pugi::xml_node nodeObjectType = nodeObject.child("tipo");
			this->generarObjeto(nodeObjectDist.text().as_int(),nodeObjectPos.text().as_string(),nodeObjectType,mapa);
		}
	}
	return mapa;
}

//Eliminamos el puntero

PistaParser::~PistaParser(){
	delete this->puntero;
}
