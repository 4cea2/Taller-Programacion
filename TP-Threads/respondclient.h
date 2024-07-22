#ifndef RESPONDCLIENT_H
#define RESPONDCLIENT_H

#include "boundedqueueblocking.h"
#include "receiver.h"
#include "sender.h"
#include "socket.h"
#include "thread.h"


/**
 * TDA RespondClient.
 *
 * Su funcion es interactuar con el cliente, incluyendo la
 * gestión de la comunicación y el mantenimiento
 * del estado del cliente.
 */
class RespondClient {
private:
    Socket peer;                     // Socket para comunicarse con el cliente.
    BoundedQueueBlocking queue_msg;  // Cola de mensajes que recibira el cliente.
    std::atomic<bool> is_alive;      // Indica si el cliente sigue en comunicacion.
    Receiver receiver;               // Hilo para recibir mensajes del cliente.
    Sender sender;                   // Hilo para enviar mensajes al cliente.
    const size_t id;                 // Identificador único del cliente.

public:
    /**
     * Constructor de la clase RespondClient.
     *
     * @param peer Socket por donde se comunicara con el cliente.
     * @param queue_gameloop Cola de mensajes para las acciones del cliente.
     * @param id Identificador único del cliente.
     */
    explicit RespondClient(Socket skt, BoundedQueueBlocking& queue_gameloop, size_t id);

    /**
     * Inicia la comunicación con el cliente.
     *
     * Inicia tanto el receptor como el emisor del cliente.
     */
    void communicate();

    /**
     * Verifica si el cliente sigue en comunicacion.
     *
     * @return true si el cliente no esta en comunicacion, false caso contrario.
     */
    bool is_dead();

    /**
     * Devuelve una referencia a la cola de mensajes del cliente.
     *
     * @return Referencia a la cola de mensajes del cliente.
     */
    BoundedQueueBlocking& get_queue_msg();

    /**
     * Devuelve el identificador único del cliente.
     *
     * @return Identificador único del cliente.
     */
    size_t get_id();

    /**
     * Intenta cerrar la comunicación con el cliente.
     */
    void leave_communicate();
};

#endif
