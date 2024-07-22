#ifndef CLIENT_H
#define CLIENT_H

#include <list>
#include <string>

#include "protocol.h"
#include "socket.h"

/**
 * TDA Client.
 * Su funcion es comunicarse con el servidor a través de un
 * protocolo.
 */
class Client {
private:
    Socket skt;
    Protocol protocol;
    std::list<std::string> msjs;

public:
    explicit Client(const char* hostname, const char* servname);


    /**
     * Lee la entrada standar y lo guarda en memoria.
     */
    void read_standar_input();

    /**
     * Verifica si se proporcionan los argumentos esperados.
     * Retorna falso si los argumentos no son lo esperados, caso
     * contrario, verdadero.
     */
    static bool arguments_checker(int argc, const char* args[]);

    /**
     * Se empieza a comunicar con el servidor enviando/recibiendo mensajes.
     * Imprime todo lo que recibio del servidor.
     */
    void communicate_with_the_server();

    /**
     * Desabilito las copias
     */
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    /**
     * Permito el movimiento de objetos
     */
    Client(Client&&) = default;
    Client& operator=(Client&&) = default;
};

#endif
