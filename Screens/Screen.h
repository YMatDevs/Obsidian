//
// Created by yashmathur on 5/21/25.
//

#ifndef SCREEN_H
#define SCREEN_H
#include <memory>
#include <vector>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Minimap/MiniMap.h"
#include "../SpaceMap/SpaceMap.h"
#include "../Sprites/Asteroid/Asteroid.h"
#include "../Sprites/Bullet/Bullets.h"
#include "../Sprites/Player/Player.h"

#define MAP_BUFFER 1024

class Screen {
public:
    virtual void update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) = 0;
    virtual void render(sf::RenderWindow& window, Screen* screen) = 0;
    virtual ~Screen() = default;
};

class MainMenuScreen : public Screen {
private:
    sf::Font font;
    sf::Text gameTitleText;
    sf::Text PlayButtonText;
    sf::RectangleShape PlayButtonRect;

    sf::Color ButtonColorDefault = sf::Color(100, 100, 255);
    sf::Color ButtonColorSelected = sf::Color(150, 150, 255);
    sf::Color ButtonColorPressed = sf::Color(200, 200, 255);
    sf::Color textColor = sf::Color::White;

    sf::Vector2f windowSize;

public:
    explicit MainMenuScreen(sf::Vector2f windowSize);
    ~MainMenuScreen() override;

    void update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) override;
    void render(sf::RenderWindow& window, Screen* screen) override;
};

class GameScreen : public Screen {
private:
    SpaceMap spaceMap;
    MiniMap minimap;
    Player player;
    sf::View playerView;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;

public:
    explicit GameScreen(sf::Vector2f windowSize);
    ~GameScreen() override;

    void update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) override;
    void render(sf::RenderWindow& window, Screen* screen) override;
};





#endif //SCREEN_H
