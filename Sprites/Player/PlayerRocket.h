//
// Created by yashmathur on 5/17/25.
//

#ifndef PLAYERROCKET_H
#define PLAYERROCKET_H

#include <SFML/Graphics.hpp>
#include <string>

class PlayerRocket {
    private:
    sf::Texture texture;
    float movementSpeed;
    float rotationSpeed;


    public:
    PlayerRocket(std::string choice);
    sf::Sprite sprite;

    void move(float offsetX, float offsetY);

    void rotate(float deltaTime);

};




#endif //PLAYERROCKET_H
