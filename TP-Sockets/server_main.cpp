#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "protocol.h"
#include "server.h"

#define SUCCESS 0
#define ERROR 1


int main(int argc, const char* argv[]) {
    // Verifico argumentos
    if (Server::arguments_checker(argc, argv)) {
        return ERROR;
    }

    // Almaceno los argumentos
    const char* servname = argv[1];

    // Creo al servidor, estableciendo conexion con el cliente
    Server server(servname);

    // Me comunico con el cliente enviando/recibiendo mensajes
    server.communicate_with_the_client();

    return SUCCESS;
}
