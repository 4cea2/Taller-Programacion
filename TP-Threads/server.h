#ifndef SERVER_H
#define SERVER_H

#include "acceptor.h"
#include "boundedqueueblocking.h"
#include "gameloop.h"
#include "resultprotected.h"
#include "socket.h"

/**
 * TDA Server.
 * Su función principal es aceptar clientes para que
 * entren al juego y cerrar el mismo.
 */
class Server {
private:
    Socket serv;  // Socket del servidor para aceptar conexiones
    BoundedQueueBlocking
            queue_gameloop;  // Cola limitada para las acciones del bucle principal del juego
    ResultProtected msg_queue_list;  // Lista protegida de mensajes recibidos del cliente
    Acceptor acceptor;               // Hilo encargado de aceptar conexiones de clientes
    GameLoop gameloop;               // Hilo para el bucle principal del juego

public:
    /**
     * Constructor de la clase Server.
     *
     * @param servname Nombre del servicio o puerto
     * en el que el servidor escuchará conexiones.
     */
    explicit Server(const char* servname);

    /**
     * Verifica si se proporcionan los argumentos esperados.
     * Registra un mensaje de error utilizando syslog si los
     * argumentos no son los esperados.
     *
     * @param argc El número de argumentos en la línea de comandos.
     * @param args Un arreglo de cadenas que contiene los argumentos
     * de la línea de comandos.
     * @return Retorna false si los argumentos no son los esperados,
     * caso contrario, true.
     */
    static bool arguments_checker(int argc, const char* args[]);

    /**
     * Lanza un aceptador de clientes para comenzar a aceptar
     * conexiones de clientes.
     */
    void accept_clients();

    /**
     * Da inicio al juego, iniciando el bucle principal del juego.
     */
    void start_game();

    /**
     * Lee la entrada estándar hasta que se detecte la letra 'q',
     * que indica el cierre del servidor y juego.
     */
    void read_standard_input();

    /**
     * Termina el juego, finalizando el aceptador de clientes, el bucle
     * principal del juego y cerrando el socket del servidor.
     */
    void end_game();

    /**
     * Deshabilita la construcción y asignación por copia de objetos.
     */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    /**
     * Permite la construcción y asignación por movimiento de objetos.
     */
    Server(Server&&) = default;
    Server& operator=(Server&&) = default;
};

#endif
