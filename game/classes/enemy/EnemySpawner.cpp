// EnemySpawner.cpp
#include "EnemySpawner.h"
#include "Enemy.h"

EnemySpawner::EnemySpawner(float interval) : spawnInterval(interval), spawnTimer(interval) {}

void EnemySpawner::update(float deltaTime, sf::RenderWindow &window)
{
    spawnTimer -= deltaTime;
    if (spawnTimer <= 0.0f)
    {
        spawnEnemy(window);
        spawnTimer = spawnInterval;
    }
}

void EnemySpawner::draw(sf::RenderWindow &window)
{
    for (auto &enemy : enemies)
    {
        enemy.draw(window);
    }
}

std::vector<Enemy> &EnemySpawner::getEnemies()
{
    return enemies;
}

std::array<int, 4> EnemySpawner::countEnemiesByRegion(const sf::RenderWindow &window) const
{
    std::array<int, 4> counts = {0, 0, 0, 0}; // Order: [above, below, left, right]

    for (const auto &enemy : enemies)
    {
        if (enemy.getPosition().y < window.getSize().y / 2)
        {
            counts[0]++;
        }
        if (enemy.getPosition().y > window.getSize().y / 2)
        {
            counts[1]++;
        }
        if (enemy.getPosition().x < window.getSize().x / 2)
        {
            counts[2]++;
        }
        if (enemy.getPosition().x > window.getSize().x / 2)
        {
            counts[3]++;
        }
    }

    return counts;
}

void EnemySpawner::spawnEnemy(sf::RenderWindow &window)
{
    float randomX = 0.0f;
    float randomY = 0.0f;
    auto counts = countEnemiesByRegion(window);

    bool spawnAbove = counts[0] < 7;
    bool spawnBelow = counts[1] < 7;
    bool spawnLeft = counts[2] < 7;
    bool spawnRight = counts[3] < 7;

    if (spawnAbove && spawnBelow && spawnLeft && spawnRight)
    {
        if (std::rand() % 2 == 0)
        {
            randomX = static_cast<float>(std::rand() % window.getSize().x);
            randomY = (std::rand() % 2 == 0) ? 0.0f : static_cast<float>(window.getSize().y);
        }
        else
        {
            randomX = (std::rand() % 2 == 0) ? 0.0f : static_cast<float>(window.getSize().x);
            randomY = static_cast<float>(std::rand() % window.getSize().y);
        }
    }
    else if (spawnAbove)
    {
        randomX = static_cast<float>(std::rand() % window.getSize().x);
        randomY = 0.0f;
    }
    else if (spawnBelow)
    {
        randomX = static_cast<float>(std::rand() % window.getSize().x);
        randomY = static_cast<float>(window.getSize().y);
    }
    else if (spawnLeft)
    {
        randomX = 0.0f;
        randomY = static_cast<float>(std::rand() % window.getSize().y);
    }
    else if (spawnRight)
    {
        randomX = static_cast<float>(window.getSize().x);
        randomY = static_cast<float>(std::rand() % window.getSize().y);
    }
    else
    {
        if (std::rand() % 2 == 0)
        {
            randomX = static_cast<float>(std::rand() % window.getSize().x);
            randomY = (std::rand() % 2 == 0) ? 0.0f : static_cast<float>(window.getSize().y);
        }
        else
        {
            randomX = (std::rand() % 2 == 0) ? 0.0f : static_cast<float>(window.getSize().x);
            randomY = static_cast<float>(std::rand() % window.getSize().y);
        }
    }

    Enemy newEnemy;
    newEnemy.initialize(sf::Vector2f(randomX, randomY), Enemy::demonTexture);
    enemies.push_back(newEnemy);
}