//Class Auto

#include "../headers/Auto.h"

#include <iostream>
using namespace std;

Auto::Auto()
{

	velocidad = 0;
	acelerando = false;

};

void Auto::acelerar(){

	acelerando = true;
	cout<<"el auto esta acelerando"<<endl;
};

void Auto::frenar(){

	if (acelerando == true){
		acelerando = false;
		cout<<"el auto esta frenando"<<endl;
	}
	else{
		cout<<"el auto ya esta frenado"<<endl;
	}
};
