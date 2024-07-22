#ifndef SENDER_H
#define SENDER_H

#include <atomic>

#include "boundedqueueblocking.h"
#include "protocol.h"
#include "socket.h"
#include "thread.h"


/**
 * TDA Sender.
 *
 * Su funcion es enviar los mensajes del juego al cliente
 * a traves de un protocolo, y avisar que se dejo de comunicar
 * con el cliente.
 */
class Sender: public Thread {
private:
    Protocol protocol;            // Protocolo para enviar los mensajes
    BoundedQueueBlocking& queue;  // Cola donde estaran los mensaje a enviar al cliente
    std::atomic<bool>& is_alive;  // Booleano que indica si se termino de comunicar con el cliente

public:
    /**
     * Constructor de la clase Sender.
     *
     * @param skt Referencia del socket por donde enviara mensajes al cliente.
     * @param queue Referencia de la cola de mensajes a enviar al cliente.
     * @param is_alive Referencia booleana que indica si el cliente esta en comunicacion.
     */
    explicit Sender(Socket& skt, BoundedQueueBlocking& queue, std::atomic<bool>& is_alive);

    /**
     * Ejecuta el hilo encargado de enviar lo que reciba del juego
     * al cliente.
     */
    virtual void run() override;

    /**
     * Destructor de la clase.
     */
    virtual ~Sender();
};

#endif
