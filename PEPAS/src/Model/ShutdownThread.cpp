//
// Created by arturi on 18/09/17.
//

#include "../../headers/Model/ShutdownThread.h"

ShutdownThread::ShutdownThread(bool &quit, Servidor *servidor) : quit(quit), srv (servidor) {

}

void ShutdownThread::run() {
    char c;
    std::cout<<"Presiona # para cerrar la conexion: "<<endl;
    std::cin >> c;
    while (c != '#'){
        std::cin >> c;
    }
    quit = true;
    srv->obtenerSocket()->CerrarConexion(srv->obtenerSocketEscucha());
    cout<<"Servidor cerro las escuchas ... "<<endl;

}

