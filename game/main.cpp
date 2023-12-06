#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "./classes/player/Player.h"
#include "./classes/magic/Fireball.h"
#include "./classes/magic/FireballSpawner.h"
#include "./classes/map/Map.h"
#include "./classes/enemy/Enemy.h"
#include "./classes/enemy/EnemySpawner.h"
#include "./classes/background/BackgroundDecorator.h"
#include "./classes/background/DecorSpawner.h"
#include "./classes/game/Game.h"

sf::Vector2f normalize(const sf::Vector2f &vector);

int main()
{
    sf::Clock clock;
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Survival Game", sf::Style::Fullscreen);

    Map gameMap;

    Game game;

    Enemy::initializeTexture();
    const float ENEMY_SPAWN_INTERVAL = 0.3f;
    float enemySpawnTimer = ENEMY_SPAWN_INTERVAL;
    EnemySpawner spawner(enemySpawnTimer);
    std::vector<Enemy> enemies;

    Player player;
    player.playerInitialize();
    sf::Vector2f directionToPlayer;
    std::string side = "down";
    const int playerSpeed = 400;

    const int maxFireballs = 7;
    float spawnTimer = 0.0f;
    Fireball::initializeTexture();
    std::vector<Fireball> fireballs;

    FireballSpawner fireballSpawner(1.0f);

    sf::Vector2f lastPlayerPosition = player.getPosition();

    std::vector<BackgroundDecorator> decorations;
    BackgroundDecorator::initializeTexture();
    const float DECORATION_SPAWN_INTERVAL = 1.4f;
    float decorationSpawnTimer = DECORATION_SPAWN_INTERVAL;

    DecorSpawner decorationSpawner(decorationSpawnTimer);

    while (window.isOpen())
    {
        sf::Event event;
        window.pollEvent(event);
        const float deltaTime = clock.restart().asSeconds();

        spawnTimer += deltaTime;

        sf::Vector2f playerPosition = player.getPosition();

        auto &fireballs = fireballSpawner.getFireballs();
        fireballSpawner.update(deltaTime, window, maxFireballs, playerPosition);

        for (auto &fireball : fireballs)
        {
            fireball.initialize(playerPosition, deltaTime);
        }

        auto &enemies = spawner.getEnemies();
        spawner.update(deltaTime, window);

        sf::Vector2f movement(0.f, 0.f);
        player.getMovement(side, movement);
        game.gameKeys(window);

        if (movement.x != 0.f || movement.y != 0.f)
        {
            movement = normalize(movement) * (playerSpeed * deltaTime);
            for (auto &enemy : enemies)
            {
                enemy.move(-movement);
            }
        }

        auto &decorations = decorationSpawner.getDecorations();
        decorationSpawner.update(side, deltaTime, window);
        if (movement.x != 0.f || movement.y != 0.f)
        {
            movement = normalize(movement) * (playerSpeed * deltaTime);
            for (auto &decoration : decorations)
            {
                decoration.move(-movement);
            }
        }

        const float enemySpeed = 100.0f;
        for (auto &enemy : enemies)
        {
            directionToPlayer = playerPosition - enemy.getPosition();
            sf::Vector2f normalizedDirection = normalize(directionToPlayer);

            enemy.move(normalizedDirection * enemySpeed * deltaTime);
        }

        for (size_t i = 0; i < enemies.size(); ++i)
        {
            for (size_t j = i + 1; j < enemies.size(); ++j)
            {
                enemies[i].repulseFrom(enemies[j]);
                enemies[j].repulseFrom(enemies[i]);
            }
        }

        for (auto it = enemies.begin(); it != enemies.end();)
        {
            sf::Vector2f position = it->getPosition();
            if (position.x > window.getSize().x + 500 || position.x < -500 ||
                position.y > window.getSize().y + 500 || position.y < -500)
            {
                it = enemies.erase(it);
            }

            if (player.intersects(it->getSprite()))
            {
                it = enemies.erase(it);
                // while (true)
                // {
                //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                //     {
                //         window.close();
                //     }
                // }
            }
            else
            {
                ++it;
            }
        }

        auto fireballIt = fireballs.begin();
        while (fireballIt != fireballs.end())
        {
            bool collisionDetected = false;

            sf::FloatRect fireballBounds = fireballIt->getSprite().getGlobalBounds();

            for (size_t i = 0; i < enemies.size(); ++i)
            {
                sf::FloatRect enemyBounds = enemies[i].getSprite().getGlobalBounds();

                if (fireballBounds.intersects(enemyBounds))
                {
                    collisionDetected = true;
                    enemies.erase(enemies.begin() + i);
                    --i;
                    break;
                }
            }

            if (collisionDetected)
            {
                fireballs.erase(fireballIt);
            }
            else
            {
                ++fireballIt;
            }
        }

        window.clear();
        gameMap.draw(window);
        player.draw(window);
        fireballSpawner.draw(window);
        spawner.draw(window);
        decorationSpawner.draw(window);

        window.display();
    }

    return 0;
}
