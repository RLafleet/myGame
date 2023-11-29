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

sf::Vector2f normalize(const sf::Vector2f &vector);

int main()
{
    sf::Clock clock;
    bool invisible = false;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Survival Game", sf::Style::Fullscreen);

    //map
    Map gameMap;

    //player
    const int playerSpeed = 200;

    sf::Texture heroSpDown;
    if (!heroSpDown.loadFromFile("./game/Texture/playerTexture/heroSpDown.png"))
    {
        std::cout << "Failed to load player texture." << std::endl;
    }
    sf::Texture heroSpUp;
    if (!heroSpUp.loadFromFile("./game/Texture/playerTexture/heroSpUp.png"))
    {
        std::cout << "Failed to load player texture." << std::endl;
    }
    sf::Texture heroSpRight;
    if (!heroSpRight.loadFromFile("./game/Texture/playerTexture/heroSpRight.png"))
    {
        std::cout << "Failed to load player texture." << std::endl;
    }
    sf::Texture heroSpLeft;
    if (!heroSpLeft.loadFromFile("./game/Texture/playerTexture/heroSpLeft.png"))
    {
        std::cout << "Failed to load player texture." << std::endl;
    }

    Player player;

    player.playerTexture(heroSpDown);

    sf::Vector2f directionToPlayer;

    // enemies
    std::vector<Enemy> enemies;

    const float ENEMY_SPAWN_INTERVAL = 0.3f;
    float enemySpawnTimer = ENEMY_SPAWN_INTERVAL;
    EnemySpawner spawner(enemySpawnTimer);

    sf::Texture demonTexture;
    if (!demonTexture.loadFromFile("./game/Texture/enemyTexture/demon.png"))
    {
        std::cout << "Failed to load demon texture." << std::endl;
    }

    // fireballs
    const int maxFireballs = 7;
    float spawnTimer = 0.0f;
    std::vector<Fireball> fireballs;

    const float FIREBALLS_SPAWN_INTERVAL = 1.0f;
    float fireballSpawnTimer = FIREBALLS_SPAWN_INTERVAL;
    FireballSpawner fireballSpawner(fireballSpawnTimer);

    sf::Texture fireballTexture;
    if (!fireballTexture.loadFromFile("./game/Texture/magicTexture/fireBall.png"))
    {
        std::cout << "Failed to load fireball texture." << std::endl;
    }

    sf::Vector2f lastPlayerPosition = player.getPosition();

    //decor
    std::vector<BackgroundDecorator> decorations;
    sf::Texture decorationTexture;
    if (!decorationTexture.loadFromFile("./game/Texture/backgroundTexture/bush.png"))
    {
        std::cout << "Failed to load camp texture." << std::endl;
    }
    float spawnTimeDecoration = 0.0f;
    std::string side = "down";
    const float DECORATION_SPAWN_INTERVAL = 1.4f;
    float decorationSpawnTimer = DECORATION_SPAWN_INTERVAL;

    DecorSpawner decorationSpawner(decorationSpawnTimer);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        //delta Time
        const float deltaTime = clock.restart().asSeconds();

        spawnTimer += deltaTime;

        // //Fireballs spawn
        // if (spawnTimer >= FIREBALLS_SPAWN_INTERVAL && fireballs.size() < maxFireballs * 2)
        // {
        //     float angle = fireballs.empty() ? 0.0f : fireballs.back().getAngle() + (360.0f / maxFireballs);
        //     fireballs.emplace_back(fireballTexture, orbitRadius, angle);
        //     spawnTimer = 0.0f;
        // }
        sf::Vector2f playerPosition = player.getPosition();

        auto &fireballs = fireballSpawner.getFireballs();
        fireballSpawner.update(deltaTime, window, fireballTexture, maxFireballs, playerPosition);

        for (auto &fireball : fireballs)
        {
            fireball.initialize(playerPosition, deltaTime);
        }

        //enemies spawn
        auto &enemies = spawner.getEnemies();
        spawner.update(deltaTime, window, demonTexture);

        //Fireballs movement around Player

        sf::Vector2f movement(0.f, 0.f);

        //Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.playerTexture(heroSpDown);
            side = "down";
            movement.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player.playerTexture(heroSpLeft);
            side = "left";
            movement.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.playerTexture(heroSpRight);
            side = "right";
            movement.x += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.playerTexture(heroSpUp);
            side = "up";
            movement.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            window.close();
        }

        // Spawn decoration and move
        auto &decorations = decorationSpawner.getDecorations();
        decorationSpawner.update(side, deltaTime, window, decorationTexture);
        if (movement.x != 0.f || movement.y != 0.f)
        {
            movement = normalize(movement) * (playerSpeed * deltaTime);
            for (auto &decoration : decorations)
            {
                decoration.move(-movement);
            }
        }

        //Enemy movement
        const float enemySpeed = 100.0f;
        for (auto &enemy : enemies)
        {
            directionToPlayer = playerPosition - enemy.getPosition();
            sf::Vector2f normalizedDirection = normalize(directionToPlayer);

            enemy.move(normalizedDirection * enemySpeed * deltaTime);
        }

        if (movement.x != 0.f || movement.y != 0.f)
        {
            movement = normalize(movement) * (playerSpeed * deltaTime);
            for (auto &enemy : enemies)
            {
                enemy.move(-movement);
            }
        }

        for (size_t i = 0; i < enemies.size(); ++i)
        {
            for (size_t j = i + 1; j < enemies.size(); ++j)
            {
                enemies[i].repulseFrom(enemies[j]);
                enemies[j].repulseFrom(enemies[i]);
            }
        }

        //Enemy delete
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

        //Fireballs delete
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

        // sf::Vector2f playerPosition(window.getSize().x / 2, window.getSize().y / 2);

        //Draws
        window.clear();
        gameMap.draw(window);
        player.draw(window);

        //These part of code i should rewrite. For these i must add class fireballSpawner and rewrite class filreball
        // for (const auto &fireball : fireballs)
        // {
        //     fireball.draw(window);
        // }
        //
        fireballSpawner.draw(window);
        spawner.draw(window);
        decorationSpawner.draw(window);

        window.display();
    }

    return 0;
}
