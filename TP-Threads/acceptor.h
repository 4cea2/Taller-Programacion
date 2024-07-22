#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>

#include "respondclient.h"
#include "resultprotected.h"
#include "socket.h"

/**
 * TDA Acceptor.
 * Su funcion es de aceptar conexiones de clientes entrantes y administrar
 * los recursos asociados a cada cliente. Permite controlar el inicio y finalización
 * de la aceptación de nuevos clientes, así como también limpiar clientes que abandonaron
 * la conexion, y liberar los recursos al finalizar.
 */

class Acceptor: public Thread {
private:
    Socket& serv;  // Referencia al socket del servidor por donde aceptara clientes
    std::list<RespondClient*> clients;  // Lista de clientes aceptados
    std::atomic<bool>
            continue_accepting;  // Booleano que indica si se debe seguir aceptado clientes o no
    BoundedQueueBlocking& queue_gameloop;  // Queue donde los clientes le enviaran acciones al juego
    ResultProtected& list_queue_sender;    // Lista protegida de mensajes recibidos del cliente

    /**
     * Elimina clientes que abandonaron el servidor.
     */
    void reap_dead();

    /**
     * Finaliza todas las conexiones y libera recursos.
     */
    void kill_all();

    /**
     * Acepta a un cliente con su identificador, y verifica
     * clientes que abandonaron la conexion.
     *
     * @param id Identificador del cliente.
     */
    void accept_client(size_t id);

public:
    /**
     * Constructor de la clase Acceptor.
     *
     * @param serv Referencia al socket del servidor.
     * @param queue Referencia a la cola limitada de acciones del bucle del juego.
     * @param list Referencia a la lista protegida de mensajes recibidos del cliente.
     */
    explicit Acceptor(Socket& serv, BoundedQueueBlocking& queue, ResultProtected& list);

    /**
     * Ejecuta el hilo encargado de aceptar clientes.
     */
    virtual void run() override;

    /**
     * Finaliza la aceptación de nuevos clientes.
     */
    void finish_accepting();

    /**
     * Destructor de la clase.
     */
    virtual ~Acceptor();
};

#endif
