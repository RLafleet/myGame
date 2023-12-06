// Game.cpp

#include "Game.h"

void Game::gameKeys(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        windowClose(window);
    }
}

void Game::windowClose(sf::RenderWindow &window) const
{
    window.close();
}
