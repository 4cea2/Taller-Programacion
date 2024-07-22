
#include "resultprotected.h"

ResultProtected::ResultProtected() {}

void ResultProtected::add_msg(const std::string& msg) {
    std::unique_lock<std::mutex> lck(m);
    if (list_queues_mgs.size() == 0) {
        return;
    } else {
        for (auto& pair: list_queues_mgs) {
            BoundedQueueBlocking& queue = pair.first;
            try {
                queue.try_push(msg);
            } catch (const ClosedQueue&) {
                // Excepcion esperada: una queue de un client ah sido cerrado (es deecir,
                // dejo de estar en conexion), por ende, sigo con las demas queues.
            }
        }
    }
}

void ResultProtected::add_queue(BoundedQueueBlocking& queue, int id) {
    std::unique_lock<std::mutex> lck(m);
    list_queues_mgs.push_back(std::make_pair(std::ref(queue), id));
}


void ResultProtected::remove_queue(size_t id) {
    std::unique_lock<std::mutex> lck(m);
    auto it = list_queues_mgs.begin();
    while (it != list_queues_mgs.end()) {
        size_t id_actually = it->second;
        if (id_actually == id) {
            it = list_queues_mgs.erase(it);
        } else {
            ++it;
        }
    }
}
