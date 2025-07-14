//
// Created by yashmathur on 5/17/25.
//

#include "SpaceMap.h"
#include "../CoreFunctions/CoreFunctions.h"


SpaceMap::SpaceMap(int mapSizeX, int mapSizeY) {
    this->mapSizeX = mapSizeX * MAP_TILE_SIZE;
    this->mapSizeY = mapSizeY * MAP_TILE_SIZE;
    this->bgTexture.loadFromFile("Assets/Space Backgrounds/SpaceTile.png");
    this->bgTexture.setSmooth(true);
    bgTexture.setRepeated(true);
    this->Sprite.setTexture(this->bgTexture);
    this->Sprite.setTextureRect(sf::IntRect(0, 0, this->mapSizeX, this->mapSizeY));
    this->Sprite.setPosition(0, 0);
}

void SpaceMap::SetView(sf::View& view, float posX, float posY, float viewWidth, float viewHeight) {
    float halfWidth = viewWidth / 2.0f;
    float halfHeight = viewHeight / 2.0f;

    float maxX = mapSizeX - halfWidth;
    float maxY = mapSizeY- halfHeight;

    // Clamp camera center to stay within the bounds
    float camX = std::clamp(posX, 1024.0f, maxX);
    float camY = std::clamp(posY, 1024.0f, maxY);

    view.setCenter(camX, camY);
}


