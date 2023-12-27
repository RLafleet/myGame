// MapCreate.cpp

#include "MapCreate.h"
#include "Map.h"

std::vector<Map> &MapCreate::getGameMapParts()
{
    return gameMapParts;
}

void MapCreate::initMap()
{
    const int gridSizeX = 2080;
    const int gridSizeY = 1080;
    const int numCellsX = 20;
    const int numCellsY = 40;

    for (int i = 0; i < numCellsX; ++i)
    {
        for (int j = 0; j < numCellsY; ++j)
        {
            float posX = (i - numCellsX / 2) * gridSizeX;
            float posY = (j - numCellsY / 2) * gridSizeY;

            Map mapPart;
            mapPart.gameMapSet(sf::Vector2f(posX, posY));
            gameMapParts.push_back(mapPart);
        }
    }
}

void MapCreate::drawGameMap(sf::RenderWindow &window)
{
    for (auto &gameMapPart : gameMapParts)
    {
        gameMapPart.draw(window);
    }
}
