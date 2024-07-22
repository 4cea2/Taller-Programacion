
#include "acceptor.h"
#include "liberror.h"

Acceptor::Acceptor(Socket& serv, BoundedQueueBlocking& queue, ResultProtected& list):
        serv(serv), continue_accepting(true), queue_gameloop(queue), list_queue_sender(list) {}

void Acceptor::accept_client(size_t id) {
    Socket peer = serv.accept();
    RespondClient* client = new RespondClient(std::move(peer), queue_gameloop, id);
    list_queue_sender.add_queue(client->get_queue_msg(), id);
    client->communicate();
    reap_dead();
    clients.push_back(client);
}

void Acceptor::run() {
    for (size_t id = 0; continue_accepting; id++) {
        try {
            accept_client(id);
        } catch (const LibError& e) {
            // Excepcion esperada: no hay clientes esperando a
            // ser aceptados.
            break;
        }
    }
    kill_all();
}

/**
 * Libera el cliente y sus recursos.
 */
static void clean_client(RespondClient* c, ResultProtected& list_queue_sender) {
    c->leave_communicate();
    size_t id = c->get_id();
    list_queue_sender.remove_queue(id);
    delete c;
}

void Acceptor::reap_dead() {
    clients.remove_if([this](RespondClient* c) {
        if (c->is_dead()) {
            clean_client(c, list_queue_sender);
            return true;
        }
        return false;
    });
}

void Acceptor::finish_accepting() { continue_accepting = false; }

void Acceptor::kill_all() {
    for (auto& c: clients) {
        clean_client(c, list_queue_sender);
    }
    clients.clear();
}

Acceptor::~Acceptor() { join(); }
