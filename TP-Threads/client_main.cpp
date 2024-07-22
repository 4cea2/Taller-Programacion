#include "client.h"

#define SUCCESS 0
#define ERROR 1

int main(int argc, const char* argv[]) {
    // Verifico argumentos
    if (!Client::arguments_checker(argc, argv)) {
        return ERROR;
    }

    // Almaceno los argumentos
    const char* hostname = argv[1];
    const char* servname = argv[2];

    // Creo al cliente, estableciendo conexion con el servidor
    Client client(hostname, servname);

    // Me comunico con el servidor enviando/recibiendo mensajes
    client.communicate_with_the_server();

    return SUCCESS;
}
