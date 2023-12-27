// Enemy.cpp

#include "Enemy.h"
#include <cmath>
#include <iostream>

sf::Texture Enemy::demonTexture;
sf::Texture Enemy::demonTexture2;
sf::Texture Enemy::demonTextureBoss;

void Enemy::initializeTexture()
{
    if (!demonTexture.loadFromFile("./game/Texture/enemyTexture/demon.png"))
    {
        std::cout << "Failed to load demon texture." << std::endl;
    }

    if (!demonTexture2.loadFromFile("./game/Texture/enemyTexture/demon2.png"))
    {
        std::cout << "Failed to load demon texture." << std::endl;
    }
    if (!demonTextureBoss.loadFromFile("./game/Texture/enemyTexture/demonBoss.png"))
    {
        std::cout << "Failed to load demon texture." << std::endl;
    }
}

void Enemy::initialize(const sf::Vector2f &position)
{
    if (std::rand() % 13 == 0)
    {
        sprite.setTexture(demonTextureBoss);
        sprite.setOrigin(demonTextureBoss.getSize().x / 2.0f, demonTextureBoss.getSize().y / 2.0f);
        hp = 20;
        damage = 40;
        ex = 60;
    }
    else if (std::rand() % 2 == 0)
    {
        sprite.setTexture(demonTexture);
        sprite.setOrigin(demonTexture.getSize().x / 2.0f, demonTexture.getSize().y / 2.0f);
        hp = 2;
        damage = 10;
        ex = 20;
    }
    else
    {
        sprite.setTexture(demonTexture2);
        sprite.setOrigin(demonTexture2.getSize().x / 2.0f, demonTexture2.getSize().y / 2.0f);
        hp = 4;
        damage = 20;
        ex = 40;
    }
    sprite.setPosition(position);
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

sf::Vector2f normalize(const sf::Vector2f &vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        return sf::Vector2f(vector.x / length, vector.y / length);
    }
    return vector;
}

void Enemy::repulseFrom(const Enemy &other)
{
    const float REPULSION_DISTANCE = 70.0f;

    sf::Vector2f delta = sprite.getPosition() - other.sprite.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (distance > 0 && distance < REPULSION_DISTANCE)
    {
        sf::Vector2f repulsionDir = normalize(delta);
        float repulsionMagnitude = REPULSION_DISTANCE - distance;

        sprite.move(repulsionDir * repulsionMagnitude);
    }
}

int Enemy::getHP() const
{
    return hp;
}

void Enemy::setHP(int newHP)
{
    hp = newHP;
}

int Enemy::getEXP() const
{
    return ex;
}

void Enemy::setEXP(int newEXP)
{
    ex = newEXP;
}

int Enemy::getDMG() const
{
    return damage;
}