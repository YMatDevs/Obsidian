//
// Created by yashmathur on 5/21/25.
//

#include "Screen.h"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../CoreFunctions/CoreFunctions.h"
#include <cmath>
#include <iomanip>

/*
 *
 *
 * ************************** MAIN MENU SCREEN ***********************
 *
 *
 *
 */


MainMenuScreen::MainMenuScreen(sf::Vector2f windowSize) : _isButtonPressed(false), _isHovering(false) {
    // --- Load Assets ---
    if (!_font.loadFromFile("Assets/Fonts/futures.ttf")) {
        // Fallback to Arial if custom font fails
        _font.loadFromFile("Assets/Fonts/Arial.ttf");
    }

    if (!_backgroundTexture.loadFromFile("Assets/Space Backgrounds/SpaceTile.png")) {
        // Handle error - a simple color background can be a fallback
    }
    _backgroundTexture.setRepeated(true); // Allow the texture to tile
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setTextureRect({ 0, 0, (int)windowSize.x * 2, (int)windowSize.y * 2 }); // Use a larger rect for smooth scrolling
    _backgroundSprite.setScale(0.5f, 0.5f); // Example scaling if texture is high-res

    // --- Title ---
    _gameTitleText.setFont(_font);
    _gameTitleText.setString("ASTRO-DRIFT");
    _gameTitleText.setCharacterSize(80);
    _gameTitleText.setFillColor(sf::Color::White);
    _gameTitleText.setLetterSpacing(1.2f);
    centerOrigin(_gameTitleText); // Calls the sf::Text& overload
    _gameTitleText.setPosition(windowSize.x / 2.f, windowSize.y * 0.25f);

    // --- Button Colors ---
    _buttonColorDefault  = sf::Color(25, 35, 80, 220);
    _buttonColorSelected = sf::Color(50, 70, 160, 255);
    _buttonColorPressed  = sf::Color(15, 25, 60, 255);

    // --- Play Button Rectangle ---
    _playButtonRect.setSize({320, 80});
    _playButtonRect.setFillColor(_buttonColorDefault);
    _playButtonRect.setOutlineColor(sf::Color(120, 140, 255));
    _playButtonRect.setOutlineThickness(2);
    centerOrigin(_playButtonRect); // Calls the sf::Shape& overload
    _playButtonRect.setPosition(windowSize.x / 2.f, windowSize.y * 0.6f);

    // --- Play Button Text ---
    _playButtonText.setFont(_font);
    _playButtonText.setString("PLAY");
    _playButtonText.setCharacterSize(40);
    _playButtonText.setFillColor(sf::Color::White);
    _playButtonText.setLetterSpacing(1.1f);
    centerOrigin(_playButtonText); // Calls the sf::Text& overload
    _playButtonText.setPosition(_playButtonRect.getPosition());
}
void MainMenuScreen::update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) {
    // --- Animate Background ---
    // Scrolls the background texture slightly for a parallax effect
    sf::IntRect textureRect = _backgroundSprite.getTextureRect();
    textureRect.left += 20 * deltaTime;
    textureRect.top += 10 * deltaTime;
    _backgroundSprite.setTextureRect(textureRect);

    // --- Interaction Logic ---
    // IMPORTANT: Using sf::Mouse::getPosition() gets mouse coords relative to the DESKTOP.
    // This will only work correctly if the window is at position (0,0).
    // To fix this, your base Screen::update should pass the sf::RenderWindow&.
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
    _isHovering = _playButtonRect.getGlobalBounds().contains(mousePos);

    // Check for a click release to change screen
    if (_isHovering && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && _isButtonPressed) {
        // This line creates the new game screen. Make sure you have a GameScreen class.
        screenRef = new GameScreen(windowSize);
        return;
    }

    _isButtonPressed = _isHovering && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // --- Visual Feedback ---
    sf::Color targetColor = _buttonColorDefault;
    sf::Vector2f targetScale = {1.0f, 1.0f};
    sf::Vector2f targetPos = _playButtonRect.getPosition();

    if (_isHovering) {
        targetColor = _buttonColorSelected;
        targetScale = {1.05f, 1.05f};
    }
    if (_isButtonPressed) {
        targetColor = _buttonColorPressed;
        targetScale = {0.98f, 0.98f};
        // Move the button slightly down and right to simulate a press
        targetPos += {4.f, 4.f};
    }

    // --- FIX: Smoothly interpolate color for each channel individually ---
    float interpSpeed = 10.0f * deltaTime;
    sf::Color currentColor = _playButtonRect.getFillColor();

    sf::Uint8 r = static_cast<sf::Uint8>(currentColor.r + (targetColor.r - currentColor.r) * interpSpeed);
    sf::Uint8 g = static_cast<sf::Uint8>(currentColor.g + (targetColor.g - currentColor.g) * interpSpeed);
    sf::Uint8 b = static_cast<sf::Uint8>(currentColor.b + (targetColor.b - currentColor.b) * interpSpeed);
    sf::Uint8 a = static_cast<sf::Uint8>(currentColor.a + (targetColor.a - currentColor.a) * interpSpeed);

    _playButtonRect.setFillColor({r, g, b, a});

    // Smoothly interpolate scale and position
    _playButtonRect.setScale(_playButtonRect.getScale() + (targetScale - _playButtonRect.getScale()) * interpSpeed);
    _playButtonText.setScale(_playButtonRect.getScale()); // Match text scale to button
    _playButtonText.setPosition(_playButtonRect.getPosition() + (targetPos - _playButtonRect.getPosition()) * interpSpeed);
}
void MainMenuScreen::render(sf::RenderWindow& window, Screen* screen) {
    window.clear(); // No need to clear with a color if background covers everything

    // Draw background first
    window.draw(_backgroundSprite);

    // --- Draw Title with Shadow ---
    sf::Text titleShadow = _gameTitleText;
    titleShadow.move(4, 4);
    titleShadow.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(titleShadow);
    window.draw(_gameTitleText);

    // --- Draw Button with Shadow ---
    // The "pressed" effect from update() handles the shadow now, so we just draw the main elements.
    window.draw(_playButtonRect);
    window.draw(_playButtonText);
}
void MainMenuScreen::centerOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}
void MainMenuScreen::centerOrigin(sf::Shape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}




// --------- GameScreen Implementation ---------

GameScreen::GameScreen(sf::Vector2f windowSize)
    : spaceMap(20, 20), minimap(windowSize, {20 * MAP_TILE_SIZE, 20 * MAP_TILE_SIZE}), player("Fighter")
{
    player.sprite.setPosition(1024, 1024);
    playerView.setSize(sf::Vector2f(3640, 2048));
    playerView.setCenter(player.sprite.getPosition());
    bulletTexture.loadFromFile("Assets/Fighter/Charge_2.png");
    asteroidTexture.loadFromFile("Assets/Asteroid/Asteroid1.png");
    // for (int i = 0; i < 300; i++) {
    //     const Asteroid random_asteroid;
    //     asteroids.push_back(random_asteroid);
    // }
    this->GameLevel = 1;
    AsteroidSpawnMinDistance = std::max(playerView.getSize().x, playerView.getSize().y) / 2.0f + 100.0f;
    AsteroidSpawnMaxDistance = AsteroidSpawnMinDistance * 2.0f;
    timeAlive.restart();
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


inline bool circleCollision(const sf::Sprite& a, float shrinkA,
                            const sf::Sprite& b, float shrinkB)
{
    sf::Vector2f posA = a.getPosition();
    sf::Vector2f posB = b.getPosition();

    float radiusA = (std::min(a.getLocalBounds().width, a.getLocalBounds().height) * a.getScale().x * 0.5f) * shrinkA;
    float radiusB = (std::min(b.getLocalBounds().width, b.getLocalBounds().height) * b.getScale().x * 0.5f) * shrinkB;

    float dx = posA.x - posB.x;
    float dy = posA.y - posB.y;
    float distSq = dx * dx + dy * dy;
    float rSum = radiusA + radiusB;

    return distSq <= (rSum * rSum);
}


void GameScreen::update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) {
    int8_t rotation = 0;
    bool thruster = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) thruster = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) rotation = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rotation = 1;

    player.move(deltaTime, thruster, rotation);
    sf::Vector2f playerPos = player.sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bullets.size() <= MAX_BULLETS && debouncer == 0) {
        const float rot = player.sprite.getRotation();
        const Bullet bullet(playerPos, rot);
        bullets.push_back(bullet);
        debouncer = BULLET_DEBOUNCE;
    }
    if ( debouncer >  0) debouncer--;

    adjust_player_bounds(playerPos, player, 20);

    // playerView.setCenter(playerPos);

    sf::Vector2f halfSize = playerView.getSize() * 0.5f;

    // Clamp X
    float viewX = std::max(halfSize.x, std::min(playerPos.x, 20 * MAP_TILE_SIZE - halfSize.x));

    // Clamp Y
    float viewY = std::max(halfSize.y, std::min(playerPos.y, 20 * MAP_TILE_SIZE - halfSize.y));

    playerView.setCenter(viewX, viewY);


    for (auto& bullet : bullets) { if (bullet.liveTime > TIME_TO_LIVE) bullets.erase(bullets.begin()); bullet.update(deltaTime); }

    float timePassed = timeAlive.getElapsedTime().asSeconds();
    if (timePassed >= 50 && timePassed < 100) GameLevel = 2;
    else if (timePassed >= 100 && timePassed < 150) GameLevel = 3;
    else if (timePassed >= 150) GameLevel = 4;

    // Asteroid Generation
    switch (GameLevel) {
        case 1:
            if (asteroids.size() < NUMBER_OF_ASTEROIDS_LEVEL1) { Asteroid new_asteroid(playerPos, AsteroidSpawnMaxDistance, AsteroidSpawnMinDistance); asteroids.push_back(new_asteroid); }
            break;

        case 2:
            if (asteroids.size() < NUMBER_OF_ASTEROIDS_LEVEL2) { Asteroid new_asteroid(playerPos, AsteroidSpawnMaxDistance, AsteroidSpawnMinDistance); asteroids.push_back(new_asteroid); }
            break;
        case 3:
            if (asteroids.size() < NUMBER_OF_ASTEROIDS_LEVEL3) { Asteroid new_asteroid(playerPos, AsteroidSpawnMaxDistance, AsteroidSpawnMinDistance); asteroids.push_back(new_asteroid); }
            break;
        default:
            if (asteroids.size() < 200 ) { Asteroid new_asteroid(playerPos, AsteroidSpawnMaxDistance, AsteroidSpawnMinDistance); asteroids.push_back(new_asteroid); }
    }

    // Asteroid Movement and Collision
    for (size_t i = 0; i < asteroids.size(); i++) {

        // Asteroid Movement
        asteroids[i].update(deltaTime);

        // Map bounds
        const float currentMapWidth  = 20 * 2048.0f;
        const float currentMapHeight = 20 * 2048.0f;

        // Despawn buffer
        float despawnBuffer = 500.0f;

        sf::FloatRect despawnZone(
            playerPos.x - playerView.getSize().x / 2.0f - despawnBuffer,
            playerPos.y - playerView.getSize().y / 2.0f - despawnBuffer,
            playerView.getSize().x + despawnBuffer * 2.0f,
            playerView.getSize().y + despawnBuffer * 2.0f
        );

        asteroids.erase(
            std::remove_if(asteroids.begin(), asteroids.end(),
                [&](Asteroid &a) {
                    a.update(deltaTime);
                    sf::Vector2f pos = a.sprite.getPosition(); // Getter for position

                    bool outOfDespawnZone = !despawnZone.contains(pos);
                    bool outOfMapBounds   = (pos.x < 0.0f || pos.x > currentMapWidth ||
                                             pos.y < 0.0f || pos.y > currentMapHeight);

                    return outOfDespawnZone || outOfMapBounds;
                }
            ),
            asteroids.end()
        );




        auto asteroidBounds = asteroids[i].sprite.getGlobalBounds();

        for (size_t j = 0; j < bullets.size(); j++) {
            if (bullets[j].sprite.getGlobalBounds().intersects(asteroidBounds)) {
                asteroids.erase(asteroids.begin() + i);
                bullets.erase(bullets.begin() + j);
                i--;
                break;
            }
        }

        // Asteroid Player Collison
        if (circleCollision(player.sprite, 0.5f, asteroids[i].sprite, asteroids[i].collisionShrink)) {
            screenRef = new EndScreen(windowSize, timeAlive.getElapsedTime().asSeconds());
            return;
        }
    }
}

void GameScreen::render(sf::RenderWindow& window, Screen* screen) {
    // Main view
    window.setView(playerView);
    window.clear(sf::Color::Black);
    window.draw(spaceMap.Sprite);
    window.draw(player.sprite);

    // Bullets
    for (auto& bullet : bullets) { window.draw(bullet.sprite); }

    // Asteroids
    for (auto& asteroid : asteroids) { window.draw(asteroid.sprite); }

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


/*
 * *******************************************************************
 * *******************************************************************
 * ************************** END SCREEN *****************************
 * *******************************************************************
 * *******************************************************************
 * *******************************************************************
 */

EndScreen::EndScreen(sf::Vector2f windowSize, float timeAlive)
    : _isButtonPressed(false), _isHovering(false)
{
    // --- Load Assets ---
    if (!_font.loadFromFile("Assets/Fonts/futures.ttf")) {
        _font.loadFromFile("Assets/Fonts/Arial.ttf");
    }
    if (!_backgroundTexture.loadFromFile("Assets/Space Backgrounds/SpaceTile.png")) {
        // Handle error
    }
    _backgroundTexture.setRepeated(true);
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setTextureRect({ 0, 0, (int)windowSize.x * 2, (int)windowSize.y * 2 });
    _backgroundSprite.setScale(0.5f, 0.5f);

    // --- Status Text ---
    _statusText.setFont(_font);
    _statusText.setCharacterSize(80);
    _statusText.setLetterSpacing(1.2f);

    // Format time string (rounded to 2 decimal places)
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << timeAlive;
    _statusText.setString("Time Alive: " + oss.str() + "s");

    _statusText.setFillColor(sf::Color::White);
    centerOrigin(_statusText);
    _statusText.setPosition(windowSize.x / 2.f, windowSize.y * 0.25f);

    // --- Button Colors ---
    _buttonColorDefault  = sf::Color(25, 35, 80, 220);
    _buttonColorSelected = sf::Color(50, 70, 160, 255);
    _buttonColorPressed  = sf::Color(15, 25, 60, 255);

    // --- Restart Button Rectangle ---
    _restartButtonRect.setSize({320, 80});
    _restartButtonRect.setFillColor(_buttonColorDefault);
    _restartButtonRect.setOutlineColor(sf::Color(120, 140, 255));
    _restartButtonRect.setOutlineThickness(2);
    centerOrigin(_restartButtonRect);
    _restartButtonRect.setPosition(windowSize.x / 2.f, windowSize.y * 0.6f);

    // --- Restart Button Text ---
    _restartButtonText.setFont(_font);
    _restartButtonText.setString("RESTART");
    _restartButtonText.setCharacterSize(40);
    _restartButtonText.setFillColor(sf::Color::White);
    _restartButtonText.setLetterSpacing(1.1f);
    centerOrigin(_restartButtonText);
    _restartButtonText.setPosition(_restartButtonRect.getPosition());
}


EndScreen::~EndScreen() {}

void EndScreen::update(float deltaTime, sf::Vector2f windowSize, Screen*& screenRef) {
    // Animate Background
    sf::IntRect textureRect = _backgroundSprite.getTextureRect();
    textureRect.left += 10 * deltaTime; // Slower scroll for a more somber mood
    _backgroundSprite.setTextureRect(textureRect);

    // Interaction Logic
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
    _isHovering = _restartButtonRect.getGlobalBounds().contains(mousePos);

    // Check for a click release to change screen back to the main menu
    if (_isHovering && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && _isButtonPressed) {
        screenRef = new MainMenuScreen(windowSize);
        return;
    }

    _isButtonPressed = _isHovering && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    // Visual Feedback
    sf::Color targetColor = _buttonColorDefault;
    sf::Vector2f targetScale = {1.0f, 1.0f};
    sf::Vector2f targetPos = _restartButtonRect.getPosition();

    if (_isHovering) {
        targetColor = _buttonColorSelected;
        targetScale = {1.05f, 1.05f};
    }
    if (_isButtonPressed) {
        targetColor = _buttonColorPressed;
        targetScale = {0.98f, 0.98f};
        targetPos += {4.f, 4.f};
    }

    float interpSpeed = 10.0f * deltaTime;
    sf::Color currentColor = _restartButtonRect.getFillColor();

    sf::Uint8 r = static_cast<sf::Uint8>(currentColor.r + (targetColor.r - currentColor.r) * interpSpeed);
    sf::Uint8 g = static_cast<sf::Uint8>(currentColor.g + (targetColor.g - currentColor.g) * interpSpeed);
    sf::Uint8 b = static_cast<sf::Uint8>(currentColor.b + (targetColor.b - currentColor.b) * interpSpeed);
    sf::Uint8 a = static_cast<sf::Uint8>(currentColor.a + (targetColor.a - currentColor.a) * interpSpeed);

    _restartButtonRect.setFillColor({r, g, b, a});
    _restartButtonRect.setScale(_restartButtonRect.getScale() + (targetScale - _restartButtonRect.getScale()) * interpSpeed);
    _restartButtonText.setScale(_restartButtonRect.getScale());
    _restartButtonText.setPosition(_restartButtonRect.getPosition() + (targetPos - _restartButtonRect.getPosition()) * interpSpeed);
}

void EndScreen::render(sf::RenderWindow& window, Screen* screen) {
    window.clear();
    window.draw(_backgroundSprite);

    // Draw Status Text with Shadow
    sf::Text statusShadow = _statusText;
    statusShadow.move(4, 4);
    statusShadow.setFillColor(sf::Color(0, 0, 0, 100));
    window.draw(statusShadow);
    window.draw(_statusText);

    // Draw Button
    window.draw(_restartButtonRect);
    window.draw(_restartButtonText);
}

void EndScreen::centerOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

void EndScreen::centerOrigin(sf::Shape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}