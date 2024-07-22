#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "socket.h"


/**
 * TDA Protocol.
 * Su funcion es enviar/recibir mensajes, ya sea
 * del cliente o servidor.
 */
class Protocol {
private:
    Socket& skt;
    bool is_client;

public:
    /**
     * Construyo el protocolo en funcion del socket al cual quieren
     * comunicarse, y que rol cumple.
     */
    Protocol(Socket& skt, bool is_client);


    /**
     * Serializa y envia el msj al destinario correspondiente.
     * Retorna false si no se pudo enviar el msj.
     * Retorna true en caso contrario.
     */
    bool send_msj(std::string& msj);

    /**
     * Recibe y deserializa el msj, almacenandolo en msj_buff.
     * Retorna false si no se pudo recibir el mensaje.
     * Retorna true en caso contrario.
     */
    bool recv_msj(std::string& msj_recv);

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
