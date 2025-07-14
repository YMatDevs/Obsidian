//
// Created by yashmathur on 6/8/25.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "../Spaceships/Spaceship.h"

class Enemy : public Spaceship {
    private:
    float currentHealth;

public:
    Enemy(const std::string choice);
    // void takeDamage(int damage);
};

#endif //ENEMY_H
