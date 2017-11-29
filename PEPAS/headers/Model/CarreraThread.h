#ifndef HEADERS_MODEL_CARRERATHREAD_H_
#define HEADERS_MODEL_CARRERATHREAD_H_

#include "thread.h"
#include "servidor.h"

class CarreraThread : public Thread{
private:
	bool estaCerrado;
	Servidor* servidor;

public:
	CarreraThread(bool estaCerrado);

	void setServidor(Servidor* servidor);

    virtual void run();

    void terminar();
};

#endif /* HEADERS_MODEL_CARRERATHREAD_H_ */
