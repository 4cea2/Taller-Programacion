#include "enemy.h"

Enemy::Enemy(): state(true) {}

bool Enemy::is_alive() { return state; }

void Enemy::kill() { state = false; }

void Enemy::revive() { state = true; }
