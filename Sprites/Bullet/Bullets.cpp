//
// Created by yashmathur on 5/31/25.
//

#include "Bullets.h"

#include <iostream>
#include <ostream>
#include <cmath>
#include "../../CoreFunctions/CoreFunctions.h"

Bullet::Bullet( const sf::Vector2f bulletPosition, const float rotation) {
    // this->texture.loadFromFile("Assets/Fighter/Charge_1.png");
    sprite.setTexture(bulletTexture);
    const auto bulletSize = sf::Vector2f(sprite.getTexture()->getSize());
    sprite.setOrigin(bulletSize.x/2, bulletSize.y/2);
    sprite.setPosition(bulletPosition);
    this->rotation = rotation;
    sprite.setRotation(rotation);
    liveTime = 0.0f;
}

void Bullet::update(float deltaTime) {
    float angleRad = rotation * (3.14159265f / 180.0f);  // Convert degrees to radians
    float dx = std::cos(angleRad) * BULLET_SPEED * deltaTime;
    float dy = std::sin(angleRad) * BULLET_SPEED * deltaTime;
    sprite.move(dx, dy);
    liveTime += deltaTime;
}


Bullet::~Bullet()  = default;


