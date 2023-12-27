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
        speed.quot = 1;
    fireballSpawnTimer -= deltaTime * (speed.quot);
    int i = 0;
    if (fireballSpawnTimer <= 0.0f)
    {
        i++;
        if (i == 30)
            i = 1;
        addFireball(deltaTime, window, levelPlayer, playerCenter, i);
        fireballSpawnTimer = fireballSpawnInterval;
    }
}

void FireballSpawner::addFireball(float deltaTime, sf::RenderWindow &window, int levelPlayer, const sf::Vector2f &playerCenter, int &i)
{
    const float orbitRadius = 240.0f;
    int damageFireball = 1;
    levelPlayer += 3;
    if (fireballs.size() < levelPlayer)
    {
        float angle = fireballs.empty() ? 0.0f : fireballs.back().getAngle() + (360.0f / levelPlayer) + (i * 12);
        fireballs.emplace_back(orbitRadius, angle, damageFireball);
    }
    for (auto &fireball : fireballs)
    {
        fireball.initialize(playerCenter, deltaTime);
    }

    sf::Vector2f movement(0.f, 0.f);
}
