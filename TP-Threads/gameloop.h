#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <list>
#include <string>

#include "boundedqueueblocking.h"
#include "partida.h"
#include "resultprotected.h"
#include "thread.h"

/**
 * TDA Gameloop
 * Su funcion es hacer el loop del juego, donde en cada iteracion, matara/revivira
 * enemigos en la partida, en funcion de las acciones que hacen los clientes a traves
 * de una queue.
 */
class GameLoop: public Thread {
private:
    Partida partida;                       // Partida en donde moriran/reviviran enemigos
    BoundedQueueBlocking& queue_gameloop;  // Queue donde procesa las acciones
    bool state;                        // Booleano que indica si el juego sigue o hay que terminarlo
    ResultProtected& list_queue_msg;   // Lista de queue de mensajes a enviar a los clientes
    std::list<int> deaths_iterations;  // Lista de las iteraciones que llevan muerto los enemigos

    /**
     * Intenta matar/revivir un enemigo.
     * En caso de que suceda, imprime por pantalla el estado de la partida.
     */
    void try_kill_enemy();
    void try_revive_enemy();

    /**
     * Imprime por stdout los estados de la partida
     */
    void print_to_screen(const std::string& msg);

public:
    /**
     * Constructor de la clase GameLoop.
     *
     * @param cantidad_enemigos Cantidad de enemigos en la partida.
     * @param queque_gameloop Referencia de la queue de acciones a hacer en la partida.
     * @param list_queue_msg Lista de queue de mensajes a enviar a los clientes
     */
    explicit GameLoop(size_t cantidad_enemigos, BoundedQueueBlocking& queque_gameloop,
                      ResultProtected& list_queue_msg);

    /**
     * Termina el juego cortando el loop.
     */
    void end_game();

    /**
     * Ejecuta el hilo encargado hacer el loop y matar/revivir enemigos
     * en funcion de lo que hace el cliente
     */
    virtual void run() override;

    /**
     * Destructor de la clase.
     */
    virtual ~GameLoop();
};

#endif
