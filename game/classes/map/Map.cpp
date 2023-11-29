// Map.cpp

#include "Map.h"

Map::Map()
{
    backgroundRect.setSize(sf::Vector2f(1920.0f, 1080.0f));
    backgroundRect.setFillColor(sf::Color::Black);
    backgroundRect.setOrigin(1920.0f / 2.0f, 1080.0f / 2.0f);
    backgroundRect.setPosition(1000, 500);
}

void Map::draw(sf::RenderWindow &window)
{
    window.draw(backgroundRect);
}
