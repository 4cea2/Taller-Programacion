#include <sstream>

#include "sender.h"

Sender::Sender(Socket& skt, BoundedQueueBlocking& queue, std::atomic<bool>& is_alive):
        protocol(skt, false), queue(queue), is_alive(is_alive) {}

/**
 * Formatea el string a uno que sea facil para el protocolo.
 *
 * @param event_string Referencia del string a formatear.
 * @return string con el formato aplicado al parametro.
 */
std::string format_event_string(const std::string& event_string) {
    int alive_count = 0;
    int dead_count = 0;
    std::string event_type;

    std::string word;
    std::istringstream iss(event_string);

    iss >> word;
    iss >> word;
    iss >> word;
    iss >> event_type;
    iss >> alive_count;
    iss >> word;
    iss >> word;
    iss >> dead_count;

    std::string formatted_string =
            std::to_string(alive_count) + " " + std::to_string(dead_count) + " " + event_type;
    return formatted_string;
}

void Sender::run() {
    while (true) {
        try {
            const std::string msg = format_event_string(queue.pop());

            if (protocol.send_msg(msg)) {
                continue;
            } else {
                return;
            }
        } catch (const ClosedQueue&) {
            // Excepcion esperada: el receiver me cerro la queue, es decir,
            // que el cliente dejo de estar en comunicacion.
            return;
        }
    }
}

Sender::~Sender() {
    is_alive = false;
    this->join();
}
