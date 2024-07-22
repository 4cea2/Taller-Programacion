#ifndef RESULTPROTECTED_H
#define RESULTPROTECTED_H

#include <list>
#include <mutex>
#include <string>
#include <utility>

#include "boundedqueueblocking.h"

/**
 * TDA ResultProtected.
 *
 * Su funcion es proteger con un monitor una lista donde
 * se almacenan las queues de los sender.
 */
class ResultProtected {
private:
    std::mutex m;                                                      // Mutex
    std::list<std::pair<BoundedQueueBlocking&, int>> list_queues_mgs;  // Lista del par <queue, int>

public:
    /**
     * Constructor de la clase ResultProtected.
     */
    ResultProtected();

    /**
     * Agrega un mensaje a lista de queues.
     *
     * @param msg Referencia de un string a agregar a la lista.
     */
    void add_msg(const std::string& msg);

    /**
     * Agrega una queue a la lista con su id.
     *
     * @param queue Referencia de la queue a agregar a la lista.
     * @param id Entero que identifica a la queue.
     */
    void add_queue(BoundedQueueBlocking& queue, int id);


    /**
     * Remueve una queue de la lista en funcion de su id.
     *
     * @param id Entero que identifica a la queue.
     */
    void remove_queue(size_t id);

    /**
     * Deshabilita la construcción y asignación por copia de objetos.
     */
    ResultProtected(const ResultProtected&) = delete;
    ResultProtected& operator=(const ResultProtected&) = delete;

    /**
     * Permite la construcción y asignación por movimiento de objetos.
     */
    ResultProtected(ResultProtected&&);
    ResultProtected& operator=(ResultProtected&&);
};

#endif
