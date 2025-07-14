//
// Created by yashmathur on 5/17/25.
//

#ifndef SPACEMAP_H
#define SPACEMAP_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

class SpaceMap {
private:
    int mapSizeX;
    int mapSizeY;
    sf::Texture bgTexture;

public:
    sf::Sprite Sprite;
    SpaceMap(int mapSizeX, int mapSizeY);
    void SetView(sf::View& view, float posX, float posY, float width, float height);
};

#endif //SPACEMAP_H
