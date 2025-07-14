//
// Created by yashmathur on 5/19/25.
//

#ifndef SPACESHIP_H
#define SPACESHIP_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


 // -------- MACROS -----------//
#define TURN_LEFT 0
#define TURN_RIGHT 1
#define ROTATION_SPEED 200
#define ACCELERATION 500
#define DRAG 0.1f

#define BOMBER "Bomber"
#define CORVETTE "Corvette"
#define FIGHTER "Fighter"



class Spaceship {
protected: // or public: depending on your design
    // Spaceship Attributes
    // int maxSpeed;
    sf::Vector2i currentSpeed;
    sf::Vector2f position;

    // Graphic Objects
    sf::Texture texture;

public:
    sf::Sprite sprite;
    void move(float deltaTime, bool thrust, int8_t direction);
    void stop();
    Spaceship(int maxSpeed, sf::Vector2f position, const std::string& choice);
};



#endif //SPACESHIP_H
