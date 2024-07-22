#include "constant_queue.h"
#include "liberror.h"
#include "respondclient.h"

RespondClient::RespondClient(Socket skt, BoundedQueueBlocking& queue_gameloop, size_t id):
        peer(std::move(skt)),
        queue_msg(MAX_ACTIONS),
        is_alive(true),
        receiver(peer, queue_gameloop, queue_msg),
        sender(peer, queue_msg, is_alive),
        id(id) {}

void RespondClient::communicate() {
    receiver.start();
    sender.start();
}

BoundedQueueBlocking& RespondClient::get_queue_msg() { return queue_msg; }

bool RespondClient::is_dead() { return not is_alive; }

size_t RespondClient::get_id() { return id; }

void RespondClient::leave_communicate() {
    try {
        peer.shutdown(2);
        peer.close();
    } catch (const LibError& e) {
        // Excepcion esperada: el cliente cerro antes la conexion
    }
}
