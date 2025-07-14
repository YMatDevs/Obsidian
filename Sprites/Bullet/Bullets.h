//
// Created by yashmathur on 5/31/25.
//

#ifndef BULLETS_H
#define BULLETS_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../../CoreFunctions/CoreFunctions.h"

class Bullet {
    private:
    float rotation;


    public:
    sf::Sprite sprite;
    float liveTime;

    Bullet(sf::Vector2f bulletPosition, float rotation);
    ~Bullet();
    void update(float deltaTime);
};

#endif //BULLETS_H
