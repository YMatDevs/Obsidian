//
// Created by yashmathur on 5/17/25.
//

#ifndef PLAYERROCKET_H
#define PLAYERROCKET_H

#include <SFML/Graphics.hpp>
#include <string>
#include "../Spaceships/Spaceship.h"


class Player : public Spaceship {
    private:
    float maxHealth;
    float currentHealth;


    public:
    Player(std::string choice);

    void takeDamage(float damage);

    void renderHealthBar(sf::RenderWindow &window);

};




#endif //PLAYERROCKET_H
