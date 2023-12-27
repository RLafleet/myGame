// Map.cpp
#include "Map.h"

sf::Texture Map::gameMapTexture;

void Map::gameMapInitialize()
{
    if (!gameMapTexture.loadFromFile("./game/Texture/map/map.jpg"))
    {
        std::cout << "Failed to load map texture." << std::endl;
    }
}

void Map::gameMapSet(sf::Vector2f pathHero)
{
    backgroundRect.setPosition(pathHero);
    backgroundRect.setTexture(gameMapTexture);
    backgroundRect.setOrigin(gameMapTexture.getSize().x / 2.0f, gameMapTexture.getSize().y / 2.0f);
}

void Map::moveMapTexture(const sf::Vector2f &offset)
{
    backgroundRect.move(offset);
}

void Map::draw(sf::RenderWindow &window)
{
    window.draw(backgroundRect);
}

sf::Vector2f Map::getPosition() const
{
    return backgroundRect.getPosition();
}