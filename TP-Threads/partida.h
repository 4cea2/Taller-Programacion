#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include <vector>

#include "enemy.h"

/**
 * TDA Partida.
 *
 * Representa a la partida con los enemigos.
 */
class Partida {
private:
    std::vector<Enemy> enemies;  // Lista de enemigos
    size_t alive_enemies;        // Cantidad de enemigos vivos

    /**
     * Devuelve el estado de la partida, avisando si un enemigo murio/revivio un enemigo.
     *
     * @param action Arreglo que indica la accion a hacer (matar/revivir).
     * @return String que representa el efecto de la accion en la partida.
     */
    std::string game_state(const char action[]);

    /**
     * Recorre la lista de enemigos verificando si se puede accionar.
     *
     * @param msg Referencia de string al cual comunicar el efecto de una accion en la partida.
     * @param action Arreglo que indica la accion a hacer (matar/revivir).
     */
    void tour_enemies(std::string& msg, const char action[]);

public:
    /**
     * Constructor de la clase Partida.
     *
     * @param qty_enemies Cantidad de enemigos en la partida.
     */
    explicit Partida(size_t qty_enemies);

    /**
     * Mata/revive a un enemigo
     *
     * @param msg String por donde se comunica si se tuve efecto la accion.
     */
    void kill_enemy(std::string& msg);
    void revive_enemy(std::string& msg);

    /**
     * Deshabilita la construcción y asignación por copia de objetos.
     */
    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;

    /**
     * Permite la construcción y asignación por movimiento de objetos.
     */
    Partida(Partida&&);
    Partida& operator=(Partida&&);
};

#endif
