#ifndef SERVER_H
#define SERVER_H

#include "protocol.h"
#include "socket.h"

/**
 * TDA Server.
 * Su funcion es comunicarse con el cliente a través de un
 * protocolo.
 */
class Server {
private:
    Socket skt;
    Protocol protocol;

public:
    explicit Server(const char* servname);

    /**
     * Verifica si se proporcionan los argumentos esperados.
     * Retorna falso si los argumentos no son lo esperados, caso
     * contrario, verdadero.
     */
    static bool arguments_checker(int argc, const char* args[]);

    /**
     * Se empieza a comunicar con el servidor enviando/recibiendo mensajes.
     * Imprime las acciones procesadas que recibio del servidor.
     */
    void communicate_with_the_client();

    /**
     * Desabilito las copias
     */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    /**
     * Permito el movimiento de objetos
     */
    Server(Server&&) = default;
    Server& operator=(Server&&) = default;
};


#endif
