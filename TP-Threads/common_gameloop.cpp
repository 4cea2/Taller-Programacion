#include <list>

#include "gameloop.h"

#define MAX_ITER 15

GameLoop::GameLoop(size_t cantidad_enemigos, BoundedQueueBlocking& queque_gameloop,
                   ResultProtected& list_queue_msg):
        partida(cantidad_enemigos),
        queue_gameloop(queque_gameloop),
        state(true),
        list_queue_msg(list_queue_msg),
        deaths_iterations() {}

/**
 * Wrapper que permite hacer un sleep con milisegundos.
 */
static void sleep_millis(int millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

/**
 * Checkea si un enemigo puede revivir una vez pasado 15 iteracciones del juego.
 * En caso de haber revivido un enemigo, @return true y la cantidad que revivieron
 * a traves de @param enemigos_to_revive.
 * Caso contrario, @return false y no modifica el @param enemigos_to_revive.
 */
static bool count_iterations(std::list<int>& l, size_t& enemigos_to_revive) {
    if (l.empty()) {
        return false;
    }
    bool enemy_revived = false;
    for (auto it = l.begin(); it != l.end();) {
        if (*it == MAX_ITER) {
            it = l.erase(it);
            enemigos_to_revive++;
            enemy_revived = true;
        } else {
            *it += 1;
            ++it;
        }
    }
    return enemy_revived;
}

void GameLoop::print_to_screen(const std::string& msg) {
    std::cout << msg << std::endl;
    list_queue_msg.add_msg(msg);
}


void GameLoop::try_kill_enemy() {
    std::string msg = "";
    while (queue_gameloop.try_pop(msg)) {
        partida.kill_enemy(msg);
        if (!msg.empty()) {
            deaths_iterations.push_back(1);
            print_to_screen(msg);
        }
    }
}

void GameLoop::try_revive_enemy() {
    std::string msg = "";
    std::size_t revived_enemies = 0;
    if (count_iterations(deaths_iterations, revived_enemies)) {
        for (size_t j = 0; j < revived_enemies; j++) {
            partida.revive_enemy(msg);
            if (!msg.empty()) {
                print_to_screen(msg);
            }
        }
    }
}

void GameLoop::run() {
    for (size_t i = 0; state; i++) {
        try_kill_enemy();
        try_revive_enemy();
        sleep_millis(200);
    }
}

void GameLoop::end_game() {
    state = false;
    queue_gameloop.close();
}

GameLoop::~GameLoop() { this->join(); }
