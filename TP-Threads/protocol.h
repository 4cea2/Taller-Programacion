#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "socket.h"


/**
 * TDA Protocol.
 *
 * Su funcion es enviar/recibir mensajes, ya sea
 * del cliente o servidor.
 */
class Protocol {
private:
    Socket& skt;     // Socket por el cual se comunicaran el cliente/servidor
    bool is_client;  // Booleano que indica si el que usa el protocolo es un cliente o servidor

public:
    /**
     * Construyo el protocolo en funcion del socket al cual quieren
     * comunicarse, y que rol cumple.
     *
     * @param skt Referencia al socket donde se comunicaran tanto cliente como servidor.
     * @param is_client Booleano que indica si es cliente o no el que usa el protocolo.
     */
    Protocol(Socket& skt, bool is_client);


    /**
     * Serializa y envia el msg al destinario correspondiente.
     *
     * @param msh Referencia del mensaje a enviar.
     * @return false en caso de no poder enviar, true caso contrario.
     */
    bool send_msg(const std::string& msg);

    /**
     * Deserializa y recibe el msg al destinario correspondiente.
     *
     * @param msg_recv Referencia del string donde estara el msg.
     * @return false en caso de no poder recibir, true caso contrario.
     */
    bool recv_msg(std::string& msg_recv);

    /**
     * Desabilito las copias
     */
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    /**
     * Permito el movimiento de objetos
     */
    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = default;
};

#endif
