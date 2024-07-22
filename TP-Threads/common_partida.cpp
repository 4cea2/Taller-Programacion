#include <cstring>

#include "partida.h"

static const char KILL[] = "KILL";
static const char REVIVE[] = "REVIVE";

Partida::Partida(size_t qty_enemies): enemies(qty_enemies), alive_enemies(qty_enemies) {}

/**
 * Funcion que compara 2 cadenas.
 *
 * @param str1 Arreglo de char 1.
 * @param str2 Arreglo de char 2.
 * @return true si ambos arreglos son iguales, false caso contrario.
 */
static bool compare_strings(const char str1[], const char str2[]) {
    return strcmp(str1, str2) == 0;
}

std::string Partida::game_state(const char action[]) {
    std::string msg = "Un enemigo ha ";
    if (compare_strings(action, KILL)) {
        msg += "muerto. ";
    } else {
        msg += "revivido. ";
    }
    size_t deads = enemies.size() - alive_enemies;
    msg += std::to_string(alive_enemies) + " vivo(s) y ";
    msg += std::to_string(deads) + " muerto(s).";
    return msg;
}

void Partida::tour_enemies(std::string& msg, const char action[]) {
    bool change_state = false;
    for (Enemy& enemy: enemies) {
        if (compare_strings(action, KILL) && enemy.is_alive()) {
            enemy.kill();
            alive_enemies--;
            change_state = true;
            break;

        } else if (compare_strings(action, REVIVE) && !enemy.is_alive()) {
            alive_enemies++;
            enemy.revive();
            change_state = true;
            break;
        }
    }
    if (change_state) {
        msg = game_state(action);
    } else {
        msg = "";
    }
}

void Partida::kill_enemy(std::string& msg) { tour_enemies(msg, KILL); }

void Partida::revive_enemy(std::string& msg) { tour_enemies(msg, REVIVE); }
