//
// Created by yashmathur on 5/18/25.
//

#include "Asteroid.h"

#include <complex>
#include <chrono>
#include <cmath>
#include <random>
#include "../../CoreFunctions/CoreFunctions.h"


Asteroid::Asteroid(sf::Vector2f playerPos, float spawnMaxDistance, float spawnMinDistance) {
    sprite.setTexture(asteroidTexture);

    static std::mt19937 gen(std::random_device{}());

    // 1️⃣ Randomly choose asteroid size type
    enum SizeType { Small, Medium, Large };
    static std::uniform_int_distribution<int> sizeDist(0, 2);
    SizeType sizeType = static_cast<SizeType>(sizeDist(gen));

    float scale = 1.f;
    switch (sizeType) {
        case Small:
            scale = std::uniform_real_distribution<float>(0.6f, 1.0f)(gen);
            collisionShrink = 0.5f; // very tight
            health = 3;
            break;
        case Medium:
            scale = std::uniform_real_distribution<float>(1.2f, 2.0f)(gen);
            collisionShrink = 0.5f;
            health = 5;
            break;
        case Large:
            scale = std::uniform_real_distribution<float>(2.2f, 3.5f)(gen);
            collisionShrink = 0.5f;
            health = 8;
            break;
    }
    sprite.setScale(scale, scale);

    // 2️⃣ Set origin to center
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    // 3️⃣ Random spawn position
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * 3.14159265f);
    std::uniform_real_distribution<float> radiusDist(spawnMinDistance, spawnMaxDistance);

    float angle = angleDist(gen);
    float radius = radiusDist(gen);

    sf::Vector2f spawnPos(
        playerPos.x + radius * std::cos(angle),
        playerPos.y + radius * std::sin(angle)
    );

    sprite.setPosition(spawnPos);
    // const float currentMapWidth  = 20 * 2048.0f;
    // const float currentMapHeight = 20 * 2048.0f;
    // static std::uniform_real_distribution<float> posX_dist(0.0f, currentMapWidth);
    // static std::uniform_real_distribution<float> posY_dist(0.0f, currentMapHeight);
    // sprite.setPosition(posX_dist(gen), posY_dist(gen));


    // 4️⃣ Random movement direction & speed
    static std::uniform_real_distribution<float> angle_dist(0.0f, 360.0f);
    float angleRad = angle_dist(gen) * (3.14159265359f / 180.f);
    static std::uniform_real_distribution<float> speed_dist(100.0f, 200.0f);
    float speed = speed_dist(gen);
    velocity.x = std::cos(angleRad) * speed;
    velocity.y = std::sin(angleRad) * speed;

    // 5️⃣ Random rotation speed
    static std::uniform_real_distribution<float> rotationSpeed_dist(-50.0f, 49.0f);
    rotationSpeed = rotationSpeed_dist(gen);
}

void Asteroid::takeDamage() {
    health -= BULLET_DAMAGE;
}



void Asteroid::update(float deltaTime) {
    sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
    sprite.rotate(rotationSpeed * deltaTime);
}


const sf::FloatRect Asteroid::getBounds() const {
    return sprite.getGlobalBounds();
}
