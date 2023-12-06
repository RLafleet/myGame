// Fireball.cpp

#include "Fireball.h"
#include <cmath>
#include <iostream>

sf::Texture Fireball::fireballTexture;

void Fireball::initializeTexture()
{
    if (!fireballTexture.loadFromFile("./game/Texture/magicTexture/fireBall.png"))
    {
        std::cout << "Failed to load fireball texture." << std::endl;
    }
}

Fireball::Fireball(const sf::Texture &texture, float radius, float initialAngle) : orbitRadius(radius), angle(initialAngle)
{
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

void Fireball::initialize(sf::Vector2f center, float deltaTime)
{
    const float orbitSpeed = 110.0f;
    angle += orbitSpeed * deltaTime;

    float radAngle = angle * (3.14159265f / 180.0f);

    sprite.setPosition(
        center.x + orbitRadius * std::cos(radAngle),
        center.y + orbitRadius * std::sin(radAngle));
}

const sf::Sprite &Fireball::getSprite() const
{
    return sprite;
}

void Fireball::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

float Fireball::getAngle() const
{
    return angle;
}
