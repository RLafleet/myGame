// BackgroundDecorator.cpp

#include "BackgroundDecorator.h"
#include <iostream>

sf::Texture BackgroundDecorator::BushTexture;

void BackgroundDecorator::initializeTexture()
{
    if (!BushTexture.loadFromFile("./game/Texture/backgroundTexture/bush.png"))
    {
        std::cout << "Failed to load camp texture." << std::endl;
    }
}

void BackgroundDecorator::draw(sf::RenderWindow &window) const
{
    window.draw(decoration);
}

void BackgroundDecorator::initialize(const sf::Vector2f &position, const sf::Texture &texture)
{
    decoration.setTexture(texture);
    decoration.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    decoration.setPosition(position);
}

void BackgroundDecorator::move(const sf::Vector2f &offset)
{
    decoration.move(offset);
}
