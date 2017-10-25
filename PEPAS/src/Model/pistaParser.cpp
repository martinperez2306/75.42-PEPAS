#include "/home/barbarasanchez/Desktop/75.42-PEPAS-servidor/PEPAS/headers/Model/pistaParser.h"

PistaParser::PistaParser(){
	this->minimapa = new Minimapa();
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

void PistaParser::girarYAvanzar(string direccion,int distancia,Objetos* objetos){

	Posicion* posicionAuxiliar = this->posicionActual;
	Posicion* posicionFinal = this->posicionActual;

	if(direccion.compare("derecho") == 0){
		posicionFinal = this->puntero->avanzar(this->posicionActual,distancia);
	}
	if(direccion.compare("derecha") == 0){
		this->puntero->girarDerecha();
		posicionFinal = this->puntero->avanzar(this->posicionActual,distancia);
	}
	if(direccion.compare("izquierda") == 0){
		this->puntero->girarIzquierda();
		posicionFinal = this->puntero->avanzar(this->posicionActual,distancia);
	}
	//ACA CREAMOS UN SUBSEGMENTO!!(OJO: CLASE SE LLAMA SEGMENTO PERO ES UN SUBSEGMENTO)
	Segmento* segm = new Segmento(posicionAuxiliar,posicionFinal);
	this->minimapa->setObjetos(segm,objetos);
	this->posicionActual = posicionFinal;
}

void PistaParser::generarObjetos(Objetos* objetos, string ladoDeLosObjetos,pugi::xml_node objeto){

	Casillero* casilleroIzquierda = objetos->getObjetoIzquierda();
	Casillero* casilleroDerecha = objetos->getObjetoDerecha();

	if(ladoDeLosObjetos.compare("derecha") == 0){
		string obj = objeto.name();
		if(obj.compare("arbol") == 0){
			casilleroDerecha->setArbol();
		}
		if(obj.compare("cartel") == 0){
			int velocidadMaxima = objeto.text().as_int();
			casilleroDerecha->setCartel(velocidadMaxima);
		}
	}
	if(ladoDeLosObjetos.compare("izquierda")== 0){
		string obj = objeto.name();
		if(obj.compare("arbol") == 0){
			casilleroIzquierda->setArbol();
		}
		if(obj.compare("cartel") == 0){
			int velocidadMaxima = objeto.text().as_int();
			casilleroIzquierda->setCartel(velocidadMaxima);
		}

	}
}


void PistaParser::parsearMinimapa(){
	pugi::xml_document documento;
		pugi::xml_parse_result result = documento.load_file("pista.xml");
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
			for (pugi::xml_node nodeSegment = nodeSegments.first_child(); nodeSegment ;nodeSegment = nodeSegment.next_sibling()){
				//Detectamos los objetos que contendra el segmento (arboles, carteles, etc)
				pugi::xml_node nodeObjects = nodeSegment.child("objetos");
				Objetos* objetos = new Objetos();
				//Buscamos de que lado estaran los objetos
				for(pugi::xml_node nodeSide = nodeObjects.first_child(); nodeSide; nodeSide = nodeSide.next_sibling()){
					//Solo puede haber en un lado del segmento un tipo de objeto (POR AHORA)
					pugi::xml_node nodeObject = nodeSide.first_child();
					this->generarObjetos(objetos,nodeSide.name(),nodeObject);
				}
				//Detectamos la ruta y creamos los segmentos de ruta con sus correspondientes objetos
				pugi::xml_node nodeRoute = nodeSegment.child("ruta");
				for(pugi::xml_node nodeDirection = nodeRoute.first_child(); nodeDirection; nodeDirection = nodeDirection.next_sibling()){
					this->girarYAvanzar(nodeDirection.name(),nodeDirection.text().as_int(),objetos);
				}

			}
		}
}

Minimapa* PistaParser::getMinimapa(){
	return this->minimapa;
}
void PistaParser::prueba(){
	this->minimapa->getAllPosiciones();
}

PistaParser::~PistaParser(){
	delete this->minimapa;
	delete this->puntero;
}


