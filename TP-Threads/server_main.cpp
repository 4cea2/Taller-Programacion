#include "server.h"

#define SUCCESS 0
#define ERROR 1

int main(int argc, const char* argv[]) {
    // Verifico argumentos
    if (!Server::arguments_checker(argc, argv)) {
        return ERROR;
    }

    // Almaceno los argumentos
    const char* servname = argv[1];

    // Creo el server
    Server server(servname);

    // Empiezo a aceptar clientes
    server.accept_clients();

    // Empiezo el juego
    server.start_game();

    // Leo de entrada standar
    server.read_standard_input();

    // Termino el juego
    server.end_game();

    return SUCCESS;
}
