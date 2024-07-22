#ifndef ENEMY_H
#define ENEMY_H

/**
 * TDA Enemy.
 *
 * Su funcion es representar a un enemigo, ya sea vivo o muerto.
 */

class Enemy {
private:
    bool state;  // Booleando que indica si esta vivo o muerto (inicialmente vivo)

public:
    /**
     * Constructor de la clase Enemy.
     */
    Enemy();

    /**
     * Nos dice el estado del enemigo.
     *
     * @return true si esta vivo. Caso contrario, falso.
     */
    bool is_alive();

    /**
     * Mata al enemigo.
     */
    void kill();

    /**
     * Revive al enemigo.
     */
    void revive();

    /**
     * Deshabilita la construcción y asignación por copia de objetos.
     */
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;

    /**
     * Permite la construcción y asignación por movimiento de objetos.
     */
    Enemy(Enemy&&);
    Enemy& operator=(Enemy&&);
};

#endif
