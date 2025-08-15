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
public:
    // Constructor now takes windowSize for initial setup
    explicit MainMenuScreen(sf::Vector2f windowSize);
    ~MainMenuScreen() override = default;

    // Correctly overrides the virtual functions from your Screen base class
    void update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) override;
    void render(sf::RenderWindow& window, Screen* screen) override;

private:
    // --- Visual Assets ---
    sf::Font _font;
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;

    // --- UI Elements ---
    sf::Text _gameTitleText;
    sf::RectangleShape _playButtonRect;
    sf::Text _playButtonText;

    // --- Button State & Colors ---
    sf::Color _buttonColorDefault;
    sf::Color _buttonColorSelected;
    sf::Color _buttonColorPressed;
    bool _isButtonPressed;
    bool _isHovering;

    // --- Private Helper Functions ---
    void centerOrigin(sf::Text& text);
    void centerOrigin(sf::Shape& shape);
};


class GameScreen : public Screen {
private:
    SpaceMap spaceMap;
    MiniMap minimap;
    Player player;
    sf::View playerView;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;
    sf::Clock timeAlive;

public:
    int GameLevel;
    float AsteroidSpawnMinDistance;
    float AsteroidSpawnMaxDistance;

    explicit GameScreen(sf::Vector2f windowSize);
    ~GameScreen() override;

    void update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) override;
    void render(sf::RenderWindow& window, Screen* screen) override;
};

class EndScreen : public Screen {
public:
    // Constructor takes window size and a boolean to determine the outcome
    EndScreen(sf::Vector2f windowSize, float timeAlive);
    virtual ~EndScreen();

    // Overridden virtual functions
    void update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) override;
    void render(sf::RenderWindow& window, Screen* screen) override;

private:
    // --- Visual Assets ---
    sf::Font _font;
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;

    // --- UI Elements ---
    sf::Text _statusText; // "YOU WON" or "GAME OVER"
    sf::RectangleShape _restartButtonRect;
    sf::Text _restartButtonText;

    // --- Button State & Colors ---
    sf::Color _buttonColorDefault;
    sf::Color _buttonColorSelected;
    sf::Color _buttonColorPressed;
    bool _isButtonPressed;
    bool _isHovering;

    // --- Helper Functions ---
    static void centerOrigin(sf::Text& text);
    static void centerOrigin(sf::Shape& shape);
};



#endif //SCREEN_H
