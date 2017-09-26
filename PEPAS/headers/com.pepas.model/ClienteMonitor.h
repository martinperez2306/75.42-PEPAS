 #include <mutex>
#include "cliente.h"
#include <string>

class clienteMonitor {
private:
    Cliente* cliente;

    std::mutex m;

public:
    explicit clienteMonitor(Cliente* cliente);

};