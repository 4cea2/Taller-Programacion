#ifndef RECEIVER_H
#define RECEIVER_H

#include "boundedqueueblocking.h"
#include "protocol.h"
#include "socket.h"
#include "thread.h"

/**
 * TDA Receiver.
 *
 * Su funcion es recibir lo que envie el cliente,
 * y comunicarselo al juego a traves de una queue.
 */
class Receiver: public Thread {
private:
    Protocol protocol;                   // Protocolo para recibir los mensajes
    BoundedQueueBlocking& queue;         // Cola donde se comunicara con el juego
    BoundedQueueBlocking& queue_sender;  // Cola que usara el sender

public:
    /**
     * Constructor de la clase Receiver.
     *
     * @param skt Referencia del socket por donde recibira lo que envie el cliente.
     * @param queue Referencia de la cola de mensajes para las acciones del cliente.
     * @param queue_sender Referencia de la cola de mensajes para enviar al cliente.
     */
    explicit Receiver(Socket& skt, BoundedQueueBlocking& queue, BoundedQueueBlocking& queue_sender);

    /**
     * Ejecuta el hilo encargado de recibir lo que envia
     * el cliente.
     */
    virtual void run() override;

    /**
     * Destructor de la clase.
     */
    virtual ~Receiver();
};

#endif
