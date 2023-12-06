// DecorSpawner.cpp

#include "DecorSpawner.h"
#include "BackgroundDecorator.h"
#include <iostream>

DecorSpawner::DecorSpawner(float interval) : decorSpawnInterval(interval), decorSpawnTimer(interval) {}

void DecorSpawner::update(std::string &side, float deltaTime, sf::RenderWindow &window)
{
    decorSpawnTimer -= deltaTime;
    if (decorSpawnTimer <= 0.0f)
    {
        addDecoration(side, window);
        decorSpawnTimer = decorSpawnInterval;
    }
}

void DecorSpawner::draw(sf::RenderWindow &window)
{
    for (auto &decoration : decorations)
    {
        decoration.draw(window);
    }
}

std::vector<BackgroundDecorator> &DecorSpawner::getDecorations()
{
    return decorations;
}

void DecorSpawner::addDecoration(const std::string &side, sf::RenderWindow &window)
{
    // This is a placeholder implementation, adjust based on your requirements
    int randomY = 100;
    int randomX = 100;

    if (side == "down")
    {
        randomY = static_cast<int>(window.getSize().y + 400);
        randomX = static_cast<int>(std::rand() % 1920);
    }
    else if (side == "up")
    {
        randomY = static_cast<int>(-400);
        randomX = static_cast<int>(std::rand() % 1920);
    }
    else if (side == "left")
    {
        randomY = static_cast<int>(std::rand() % 1920);
        randomX = static_cast<int>(-400);
    }
    else if (side == "right")
    {
        randomY = static_cast<int>(std::rand() % 1920);
        randomX = static_cast<int>(window.getSize().x + 400);
    }

    BackgroundDecorator newDecoration;
    newDecoration.initialize(sf::Vector2f(randomX, randomY), BackgroundDecorator::BushTexture);
    decorations.push_back(newDecoration);
}
