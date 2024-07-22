#include "receiver.h"

Receiver::Receiver(Socket& skt, BoundedQueueBlocking& queue, BoundedQueueBlocking& queue_sender):
        protocol(skt, false), queue(queue), queue_sender(queue_sender) {}

void Receiver::run() {
    std::string msg;
    while (true) {
        if (protocol.recv_msg(msg)) {
            try {
                queue.push(msg);
            } catch (const ClosedQueue&) {
                // Excepcion esperada: el juego termino,
                // por ende, ah cerrado la queue.
            }
        } else {
            queue_sender.close();
            break;
        }
    }
}

Receiver::~Receiver() { this->join(); }
