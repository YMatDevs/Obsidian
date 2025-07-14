//
// Created by yashmathur on 5/21/25.
//

#include "Screen.h"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../CoreFunctions/CoreFunctions.h"

// --------- MainMenuScreen Implementation ---------

MainMenuScreen::~MainMenuScreen() = default;


MainMenuScreen::MainMenuScreen(sf::Vector2f windowSize)
    : windowSize(windowSize)
{
    font.loadFromFile("Assets/Fonts/Arial.ttf");

    gameTitleText.setFont(font);
    gameTitleText.setString("Space Fighter");
    gameTitleText.setCharacterSize(60);
    gameTitleText.setFillColor(sf::Color::White);
    gameTitleText.setPosition(windowSize.x / 2.f - 200, 100);

    ButtonColorDefault = sf::Color(100, 100, 100);
    ButtonColorSelected = sf::Color(150, 150, 150);
    ButtonColorPressed = sf::Color(200, 200, 200);
    textColor = sf::Color::White;

    PlayButtonRect.setSize(sf::Vector2f(300, 80));
    PlayButtonRect.setFillColor(ButtonColorDefault);
    PlayButtonRect.setPosition(windowSize.x / 2.f - 150, windowSize.y / 2.f);

    PlayButtonText.setFont(font);
    PlayButtonText.setString("Play");
    PlayButtonText.setCharacterSize(30);
    PlayButtonText.setFillColor(textColor);
    PlayButtonText.setPosition(
        PlayButtonRect.getPosition().x + 100,
        PlayButtonRect.getPosition().y + 20
    );
}

void MainMenuScreen::update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) {
    sf::Vector2i mousePos = sf::Mouse::getPosition();  // Global position
    sf::FloatRect playBounds = PlayButtonRect.getGlobalBounds();

    // Change button color on hover
    if (playBounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition()))) {
        PlayButtonRect.setFillColor(ButtonColorSelected);

        // Handle mouse click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            screenRef = new GameScreen(windowSize);  // Replace with GameScreen
            return;
        }

    } else {
        PlayButtonRect.setFillColor(ButtonColorDefault);
    }
}

void MainMenuScreen::render(sf::RenderWindow& window, Screen* screen) {
    window.clear(sf::Color::Black);
    window.draw(gameTitleText);
    window.draw(PlayButtonRect);
    window.draw(PlayButtonText);
}


// --------- GameScreen Implementation ---------

GameScreen::GameScreen(sf::Vector2f windowSize)
    : spaceMap(20, 20), minimap(windowSize, {20 * MAP_TILE_SIZE, 20 * MAP_TILE_SIZE}), player("Fighter")
{
    player.sprite.setPosition(1024, 1024);
    playerView.setSize(sf::Vector2f(3640, 2048));
    playerView.setCenter(player.sprite.getPosition());
    bulletTexture.loadFromFile("Assets/Fighter/Charge_2.png");
    asteroidTexture.loadFromFile("Assets/Assets/Charge_3.png");

}

GameScreen::~GameScreen() = default;

void adjust_player_bounds(const sf::Vector2f& position, Player& player, int mapTiles) {
    float mapWidth = mapTiles * MAP_TILE_SIZE;
    float mapHeight = mapTiles * MAP_TILE_SIZE;


    if (position.x < 0) { player.sprite.setPosition(mapWidth - 10, position.y); }
    if (position.y < 0) { player.sprite.setPosition(position.x, mapHeight - 10); }
    if (position.x > mapWidth) { player.sprite.setPosition( 10, position.y); }
    if (position.y > mapHeight) { player.sprite.setPosition(position.x, 10); }
}

void GameScreen::update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) {
    int8_t rotation = 0;
    bool thruster = false;
    sf::Vector2f playerPos = player.sprite.getPosition();


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) thruster = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) rotation = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotation = 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bullets.size() < 51 && debouncer == 0) {
        const float rot = player.sprite.getRotation();
        const Bullet bullet(playerPos, rot);
        bullets.push_back(bullet);
        debouncer = 10;
    }
    if ( debouncer >  0) debouncer--;

    player.move(deltaTime, thruster, rotation);

    adjust_player_bounds(playerPos, player, 20);

    playerView.setCenter(playerPos);

    for (auto& bullet : bullets) { bullet.update(deltaTime); }
    for (auto& bullet : bullets) { if (bullet.liveTime > 5) bullets.erase(bullets.begin()); }

}

void GameScreen::render(sf::RenderWindow& window, Screen* screen) {
    // Main view
    window.setView(playerView);
    window.clear(sf::Color::Black);
    window.draw(spaceMap.Sprite);
    window.draw(player.sprite);

    // Bullets
    for (auto& bullet : bullets) { window.draw(bullet.sprite); }

    // MiniMap view
    minimap.playerDot.setPosition(player.sprite.getPosition());
    window.setView(minimap.view);
    window.draw(spaceMap.Sprite);
    window.draw(minimap.playerDot);

    // UI
    window.setView(window.getDefaultView());
    window.draw(minimap.rectangle);

    player.renderHealthBar(window);
}