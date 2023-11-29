// Enemy.cpp

#include "Enemy.h"
#include <cmath>

sf::Vector2f normalize(const sf::Vector2f &vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        return sf::Vector2f(vector.x / length, vector.y / length);
    }
    return vector;
}

void Enemy::initialize(const sf::Vector2f &position, const sf::Texture &texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(position);
}

void Enemy::moveTowards(const sf::Vector2f &target, float deltaTime)
{
    sf::Vector2f direction = normalize(target - sprite.getPosition());
    sprite.move(direction * 100.0f * deltaTime);
}

void Enemy::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

sf::Vector2f Enemy::getPosition() const
{
    return sprite.getPosition();
}

void Enemy::move(const sf::Vector2f &offset)
{
    sprite.move(offset);
}

const sf::Sprite &Enemy::getSprite() const
{
    return sprite;
}

void Enemy::repulseFrom(const Enemy &other)
{
    const float REPULSION_DISTANCE = 70.0f; // Set this to the minimum allowed distance between enemies

    sf::Vector2f delta = sprite.getPosition() - other.sprite.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (distance > 0 && distance < REPULSION_DISTANCE)
    {
        sf::Vector2f repulsionDir = normalize(delta);
        float repulsionMagnitude = REPULSION_DISTANCE - distance;

        sprite.move(repulsionDir * repulsionMagnitude);
    }
}