// BackgroundDecorator.cpp

#include "BackgroundDecorator.h"
#include <iostream>

sf::Texture BackgroundDecorator::skull1;
sf::Texture BackgroundDecorator::skull2;
sf::Texture BackgroundDecorator::skull3;

void BackgroundDecorator::initializeTexture()
{
    if (!skull1.loadFromFile("./game/Texture/backgroundTexture/skull1.png"))
    {
        std::cout << "Failed to load camp texture." << std::endl;
    }
    if (!skull2.loadFromFile("./game/Texture/backgroundTexture/skull2.png"))
    {
        std::cout << "Failed to load camp texture." << std::endl;
    }
    if (!skull3.loadFromFile("./game/Texture/backgroundTexture/skull3.png"))
    {
        std::cout << "Failed to load camp texture." << std::endl;
    }
}

void BackgroundDecorator::draw(sf::RenderWindow &window)
{
    window.draw(decoration);
}

void BackgroundDecorator::initialize(const sf::Vector2f &position)
{

    if (std::rand() % 2 == 0)
    {
        decoration.setTexture(skull1);
        decoration.setOrigin(skull1.getSize().x / 2.0f, skull1.getSize().y / 2.0f);
        decoration.setPosition(position);
    }
    if (std::rand() % 3 == 0)
    {
        decoration.setTexture(skull2);
        decoration.setOrigin(skull2.getSize().x / 2.0f, skull2.getSize().y / 2.0f);
        decoration.setPosition(position);
    }
    else
    {

        decoration.setTexture(skull3);
        decoration.setOrigin(skull3.getSize().x / 2.0f, skull3.getSize().y / 2.0f);
        decoration.setPosition(position);
    }
}

void BackgroundDecorator::move(const sf::Vector2f &offset)
{
    decoration.move(offset);
}

const sf::Sprite &BackgroundDecorator::getSprite() const
{
    return decoration;
}
