#include "DangerArea.h"
#include <iostream>

DangerArea::DangerArea(float spawnInterval, float despawnInterval) : fireAreaSpawnInterval(spawnInterval), fireAreaDespawnInterval(despawnInterval), fireAreaSpawnTimer(spawnInterval), fireAreaDespawnTimer(despawnInterval) {}

sf::Texture DangerArea::fireAreaTexture;
sf::Texture DangerArea::electAreaTexture;

void DangerArea::initFireArea()
{
    if (!electAreaTexture.loadFromFile("./game/Texture/magicTexture/light.png"))
    {
        std::cout << "Failed to load fireball texture." << std::endl;
    }
    if (!fireAreaTexture.loadFromFile("./game/Texture/magicTexture/fireArea.png"))
    {
        std::cout << "Failed to load fireball texture." << std::endl;
    }
}

void DangerArea::setTextureFireArea(const sf::Texture &texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

const sf::Sprite &DangerArea::getFireAreaSprite() const
{
    return sprite;
}

void DangerArea::moveFireArea(const sf::Vector2f &offset)
{
    sprite.move(offset);
}

void DangerArea::addFireArea(float deltaTime, sf::RenderWindow &window, bool &stateFireArea)
{
    fireAreaSpawnTimer -= deltaTime;
    if (fireAreaSpawnTimer <= 0.0f)
    {
        if (!stateFireArea)
        {
            sf::Vector2u windowSize = window.getSize();
            float xPos = static_cast<float>(rand() % (1200 - 400 + 1) + 400);
            float yPos = static_cast<float>(rand() % (700 - 300 + 1) + 300);
            sprite.setPosition(xPos, yPos);
            setTextureFireArea(fireAreaTexture);
        }
        stateFireArea = true;
        fireAreaDespawnTimer -= deltaTime;
    }

    if (fireAreaDespawnTimer <= 0.0f)
    {
        stateFireArea = false;
        fireAreaSpawnTimer = fireAreaSpawnInterval;
        fireAreaDespawnTimer = fireAreaDespawnInterval;
    }
}

void DangerArea::addElectArea(float deltaTime, sf::RenderWindow &window, bool &stateElectArea)
{
    fireAreaSpawnTimer -= deltaTime;
    if (fireAreaSpawnTimer <= 0.0f)
    {
        if (!stateElectArea)
        {
            sf::Vector2u windowSize = window.getSize();
            float xPos = static_cast<float>(rand() % (1200 - 400 + 1) + 400);
            float yPos = static_cast<float>(rand() % (700 - 300 + 1) + 300);
            sprite.setPosition(xPos, yPos);
            setTextureFireArea(electAreaTexture);
        }
        stateElectArea = true;
        fireAreaDespawnTimer -= deltaTime;
    }

    if (fireAreaDespawnTimer <= 0.0f)
    {
        stateElectArea = false;
        fireAreaSpawnTimer = fireAreaSpawnInterval;
        fireAreaDespawnTimer = fireAreaDespawnInterval;
    }
}

void DangerArea::drawFireArea(sf::RenderWindow &window, const bool &stateFireArea) const
{
    if (stateFireArea)
        window.draw(sprite);
}

bool DangerArea::intersectsFireArea(const sf::Sprite &other) const
{
    sf::FloatRect expandedBounds = sprite.getGlobalBounds();
    return expandedBounds.intersects(other.getGlobalBounds());
}
