// EnemySpawner.cpp
#include "EnemySpawner.h"
#include "Enemy.h"
#include "cstdlib"
#include "math.h"

EnemySpawner::EnemySpawner(float interval) : spawnInterval(interval), spawnTimer(interval) {}

void EnemySpawner::update(float deltaTime, sf::RenderWindow &window, sf::Vector2f &path)
{
    div_t spawnAmout = div(abs(path.x), 1920);
    div_t spawnAmout2 = div(abs(path.y), 1080);
    if (spawnAmout.quot == 0)
        spawnAmout.quot = 1;
    if (spawnAmout.quot > spawnAmout2.quot)
        spawnTimer -= deltaTime * abs(spawnAmout.quot);
    else
        spawnTimer -= deltaTime * abs(spawnAmout2.quot);
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
    std::array<int, 4> counts = {0, 0, 0, 0};

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

    bool spawnAbove = counts[0] < 4;
    bool spawnBelow = counts[1] < 3;
    bool spawnLeft = counts[2] < 3;
    bool spawnRight = counts[3] < 3;

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
    newEnemy.initialize(sf::Vector2f(randomX, randomY));
    enemies.push_back(newEnemy);
}