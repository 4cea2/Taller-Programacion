#ifndef CLIENT_H
#define CLIENT_H

#include "protocol.h"
#include "socket.h"

/**
 * TDA Client.
 * Su función principal es comunicarse con el servidor enviando/recibiendo
 * acciones/eventos.
 */
class Client {
private:
    Socket skt;         // Socket para la comunicación con el servidor
    Protocol protocol;  // Protocolo de comunicación

public:
    /**
     * Constructor de la clase Client.
     *
     * @param hostname El nombre del host al que se conectará el cliente.
     * @param servname El nombre del servicio o puerto al que se conectará el cliente.
     */
    explicit Client(const char* hostname, const char* servname);

    /**
     * Verifica si se proporcionan los argumentos esperados.
     * Registra un mensaje de error utilizando syslog si los
     * argumentos no son los esperados.
     *
     * @param argc El número de argumentos en la línea de comandos.
     * @param args Un arreglo de cadenas que contiene los argumentos de la línea de comandos.
     * @return Retorna false si los argumentos no son los esperados, caso contrario, verdadero.
     */
    static bool arguments_checker(int argc, const char* args[]);

    /**
     * Inicia la comunicación con el servidor enviando/recibiendo mensajes/eventos.
     * Imprime todo lo recibido del servidor.
     */
    void communicate_with_the_server();

    /**
     * Deshabilita la construcción y asignación por copia de objetos.
     */
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    /**
     * Permite la construcción y asignación por movimiento de objetos.
     */
    Client(Client&&) = default;
    Client& operator=(Client&&) = default;
};

#endif
