// FireballSpawner.cpp

#include "FireballSpawner.h"
#include "Fireball.h"
#include <iostream>
#include <math.h>
#include <cstdlib>

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

void FireballSpawner::update(float deltaTime, sf::RenderWindow &window, int levelPlayer, const sf::Vector2f &playerCenter)
{
    div_t speed = div(levelPlayer, 3);
    if (speed.quot == 0)
        speed.quot == 1;
    fireballSpawnTimer -= deltaTime * (speed.quot);
    if (fireballSpawnTimer <= 0.0f)
    {
        addFireball(deltaTime, window, levelPlayer, playerCenter);
        fireballSpawnTimer = fireballSpawnInterval;
    }
}

void FireballSpawner::addFireball(float deltaTime, sf::RenderWindow &window, int levelPlayer, const sf::Vector2f &playerCenter)
{
    const float orbitRadius = 240.0f;
    int damageFireball = 1;
    levelPlayer += 3;
    if (fireballs.size() < levelPlayer)
    {
        float angle = fireballs.empty() ? 0.0f : fireballs.back().getAngle() + (360.0f / levelPlayer);
        fireballs.emplace_back(orbitRadius, angle, damageFireball);
    }
    for (auto &fireball : fireballs)
    {
        fireball.initialize(playerCenter, deltaTime);
    }

    sf::Vector2f movement(0.f, 0.f);
}
