//
// Created by yashmathur on 5/17/25.
//

#include "Player.h"


Player::Player(const std::string choice) : Spaceship(5000, /*sf::Vector2f (4096.0f, 4096.0f)*/ sf::Vector2f(100, 100), choice)
{
    this->maxHealth = 100.0f;
    this->currentHealth = 100.0f;

}

void Player::takeDamage(float damage) {
    currentHealth -= damage;
    if (currentHealth < 0) { currentHealth = 0; }
}

void Player::renderHealthBar(sf::RenderWindow& window) {
    float barWidth = 100.0f;
    float barHeight = 20.0f;
    float healthPercentage = currentHealth / maxHealth;

    // Fixed position in top-left corner
    sf::Vector2f barPosition(20.f, 20.f);  // Adjust as needed

    // Red background (full bar)
    sf::RectangleShape background(sf::Vector2f(barWidth, barHeight));
    background.setFillColor(sf::Color::Red);
    background.setPosition(barPosition);

    // Green foreground (current health)
    sf::RectangleShape foreground(sf::Vector2f(barWidth * healthPercentage, barHeight));
    foreground.setFillColor(sf::Color::Green);
    foreground.setPosition(barPosition);
    sf::Text label;
    label.setString("HEALTH");
    label.setCharacterSize(14);
    label.setFillColor(sf::Color::White);
    label.setPosition(barPosition.x, barPosition.y - 18);
    window.draw(label);


    window.draw(background);
    window.draw(foreground);
}
