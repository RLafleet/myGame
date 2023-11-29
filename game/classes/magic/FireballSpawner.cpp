// DecorSpawner.cpp

#include "FireballSpawner.h"
#include <iostream>

FireballSpawner::FireballSpawner(float spawnInterval) : fireballSpawnInterval(spawnInterval), fireballSpawnTimer(spawnInterval) {}
void FireballSpawner::draw(sf::RenderWindow &window)
{
    for (auto &fireball : fireballs)
    {
        fireball.draw(window);
    }
}

std::vector<Fireball> &FireballSpawner::getFireballs()
{
    return fireballs;
}

void FireballSpawner::update(float deltaTime, sf::RenderWindow &window, const sf::Texture &sprite, const int &maxFireballs, const sf::Vector2f &playerCenter)
{
    fireballSpawnTimer -= deltaTime;
    if (fireballSpawnTimer <= 0.0f)
    {
        addFireball(deltaTime, window, sprite, maxFireballs, playerCenter);
        fireballSpawnTimer = fireballSpawnInterval;
    }
}

void FireballSpawner::addFireball(float deltaTime, sf::RenderWindow &window, const sf::Texture &fireballTexture, const int &maxFireballs, const sf::Vector2f &playerCenter)
{
    const float orbitRadius = 240.0f;
    if (fireballs.size() < maxFireballs * 2)
    {
        float angle = fireballs.empty() ? 0.0f : fireballs.back().getAngle() + (360.0f / maxFireballs);
        fireballs.emplace_back(fireballTexture, orbitRadius, angle);
    }

    for (auto &fireball : fireballs)
    {
        fireball.initialize(playerCenter, deltaTime);
    }

    sf::Vector2f movement(0.f, 0.f);
}
