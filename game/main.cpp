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
#include "./classes/magic/dangerArea/DangerArea.h"
#include "./classes/magic/FireballSpawner.h"
#include "./classes/map/Map.h"
#include "./classes/map/MapCreate.h"
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

    Map::gameMapInitialize();

    sf::Font font;
    if (!font.loadFromFile("./game/Texture/cyrilicOld.TTF"))
    {
        std::cerr << "Failed to load font." << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(64);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(100.f, 100.f);

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setCharacterSize(64);
    levelText.setFillColor(sf::Color::Red);
    levelText.setPosition(100.f, 200.f);

    sf::Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(64);
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition(100.f, 900.f);

    std::vector<Map> gameMapParts;
    MapCreate mapCreate;

    Game game;

    float spawnTimer = 0.0f;
    Enemy::initializeTexture();
    const float ENEMY_SPAWN_INTERVAL = 0.8f;

    EnemySpawner spawner(ENEMY_SPAWN_INTERVAL);
    std::vector<Enemy> enemies;

    bool death = false;
    sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("./game/Texture/gameOver.jpg"))
    {
        std::cout << "Failed to load game over texture." << std::endl;
    }

    sf::Sprite gameOverSprite(gameOverTexture);
    gameOverSprite.setOrigin(gameOverTexture.getSize().x / 2.0f, gameOverTexture.getSize().y / 2.0f);
    gameOverSprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    sf::Texture winTexture;
    if (!winTexture.loadFromFile("./game/Texture/win.jpg"))
    {
        std::cout << "Failed to load game over texture." << std::endl;
    }
    sf::Sprite winSprite(winTexture);
    winSprite.setOrigin(winTexture.getSize().x / 2.0f, winTexture.getSize().y / 2.0f);
    winSprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    bool startGame = false;

    sf::Texture settingsTexture, controlsTexture, startTexture, exitTexture;
    if (!controlsTexture.loadFromFile("./game/Texture/keys.png") ||
        !settingsTexture.loadFromFile("./game/Texture/settings.png") ||
        !startTexture.loadFromFile("./game/Texture/play.png") ||
        !exitTexture.loadFromFile("./game/Texture/quit.png"))
    {
        std::cerr << "Failed to load button textures." << std::endl;
        return EXIT_FAILURE;
    }

    sf::Sprite settings(settingsTexture);
    sf::Sprite startButton(startTexture);
    sf::Sprite exitButton(exitTexture);
    sf::Sprite controls(controlsTexture);

    settings.setPosition(300.f, window.getSize().y / 2.0f);
    controls.setPosition(window.getSize().x / 2.0f - 200, window.getSize().y / 2.0f - 150.f);
    startButton.setPosition(300.f, window.getSize().y / 2.0f - 300.f);
    exitButton.setPosition(300.f, window.getSize().y / 2.0f + 300.f);
    bool controlsCheck = false;

    Player player;
    player.playerInitialize();
    sf::Vector2f directionToPlayer;
    std::string side = "down";
    const int playerSpeed = 300;

    DangerArea::initFireArea();
    DangerArea dangerArea(4.0f, 2.0f);
    bool stateFireArea = false;

    DangerArea electArea(4.0f, 2.0f);
    bool stateElectArea = false;

    Fireball::initializeTexture();
    std::vector<Fireball> fireballs;

    FireballSpawner fireballSpawner(0.7f);

    sf::Vector2f lastPlayerPosition = player.getPosition();

    std::vector<BackgroundDecorator> decorations;
    BackgroundDecorator::initializeTexture();

    DecorSpawner decorationSpawner(0.1f);
    sf::Vector2f pathHero(960.f, 540.f);

    bool jojo = true;
    mapCreate.initMap();

    int expr = 100;
    sf::Vector2f path(900.f, 440.f);
    while (window.isOpen())
    {
        sf::Event event;
        window.pollEvent(event);
        if (!startGame)
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (settings.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Controls button clicked!" << std::endl;
                    controlsCheck = true;
                }
                else if (startButton.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Start button clicked!" << std::endl;
                    startGame = true;
                }
                else if (exitButton.getGlobalBounds().contains(mousePos))
                {
                    std::cout << "Exit button clicked!" << std::endl;
                    if (!controlsCheck)
                        window.close();
                }
            }
            window.clear();
            if (controlsCheck)
                window.draw(controls);
            window.draw(startButton);
            window.draw(settings);
            window.draw(exitButton);
        }
        else
        {

            const float deltaTime = clock.restart().asSeconds();

            spawnTimer += deltaTime;

            sf::Vector2f playerPosition = player.getPosition();

            auto &fireballs = fireballSpawner.getFireballs();
            fireballSpawner.update(deltaTime, window, player.getLevel(), playerPosition);

            for (auto &fireball : fireballs)
            {
                fireball.initialize(playerPosition, deltaTime);
            }
            auto &enemies = spawner.getEnemies();
            spawner.update(deltaTime, window, path);

            auto &gameMapParts = mapCreate.getGameMapParts();

            sf::Vector2f movement(0.f, 0.f);
            player.getMovement(side, movement);
            game.gameKeys(window);

            if (player.getLevel() >= 6)
            {
                auto &fireArea = electArea.getFireAreaSprite();
                electArea.addElectArea(deltaTime, window, stateElectArea);
            }

            if (player.getLevel() >= 4)
            {
                auto &fireArea = dangerArea.getFireAreaSprite();
                dangerArea.addFireArea(deltaTime, window, stateFireArea);
            }

            auto &decorations = decorationSpawner.getDecorations();
            decorationSpawner.update(side, deltaTime, window);

            if (movement.x != 0.f || movement.y != 0.f)
            {
                movement = normalize(movement) * (playerSpeed * deltaTime);
                path.x += movement.x;
                path.y += movement.y;

                for (auto &enemy : enemies)
                {
                    enemy.move(-movement);
                }
                for (auto &decoration : decorations)
                {
                    decoration.move(-movement);
                }
                dangerArea.moveFireArea(-movement);
                electArea.moveFireArea(-movement);
                pathHero += movement;

                for (auto &gameMapPart : gameMapParts)
                {
                    gameMapPart.moveMapTexture(-movement);
                }
            }

            auto it = decorations.begin();
            while (it != decorations.end())
            {
                sf::Vector2f position = it->getSprite().getPosition();

                if (position.x > window.getSize().x + 1000 || position.x < -1000 ||
                    position.y > window.getSize().y + 1000 || position.y < -1000)
                {
                    it = decorations.erase(it);
                }
                else
                {
                    ++it;
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
                else if (player.intersects(it->getSprite()))
                {
                    int currentHealth = player.getHealthPoints();
                    int damage = it->getDMG();
                    player.setHealthPoints(currentHealth - damage);

                    if (currentHealth - damage <= 0)
                    {
                        death = true;
                        player.setHealthPoints(100);
                    }

                    it = enemies.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            scoreText.setString("SCORE: " + std::to_string(expr));
            levelText.setString("Level: " + std::to_string(player.getLevel()));
            hpText.setString("HealthPoints: " + std::to_string(player.getHealthPoints()));

            for (auto it = enemies.begin(); it != enemies.end();)
            {
                sf::Vector2f position = it->getPosition();

                if (dangerArea.intersectsFireArea(it->getSprite()) && stateFireArea)
                {
                    expr += it->getEXP();
                    player.setLevel(expr);
                    it = enemies.erase(it);
                }
                else if (electArea.intersectsFireArea(it->getSprite()) && stateElectArea)
                {
                    expr += it->getEXP();
                    player.setLevel(expr);
                    it = enemies.erase(it);
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
                int fireballDamage = fireballIt->getDamage();
                for (auto it = enemies.begin(); it != enemies.end(); ++it)
                {
                    sf::FloatRect enemyBounds = it->getSprite().getGlobalBounds();

                    if (fireballBounds.intersects(enemyBounds))
                    {
                        int currentHP = it->getHP();
                        if (currentHP > 0)
                        {
                            it->setHP(currentHP - fireballDamage);
                        }

                        if (currentHP <= 1)
                        {
                            expr += it->getEXP();
                            player.setLevel(expr);
                            it = enemies.erase(it);
                        }

                        collisionDetected = true;
                        break;
                    }
                }

                if (collisionDetected)
                {
                    fireballIt = fireballs.erase(fireballIt);
                }
                else
                {
                    ++fireballIt;
                }
            }
            window.clear();
            if (path.x > 1920 * 1 || path.y < -1920 * 10 || path.y > 1080 * 10 || path.x < -1080 * 10)
            {
                window.draw(scoreText);
                window.draw(winSprite);
            }
            else
            {
                if (!death)
                {
                    mapCreate.drawGameMap(window);
                    player.draw(window);
                    decorationSpawner.draw(window);
                    fireballSpawner.draw(window);
                    dangerArea.drawFireArea(window, stateFireArea);
                    electArea.drawFireArea(window, stateElectArea);
                    spawner.draw(window);

                    window.draw(scoreText);
                    window.draw(levelText);
                    window.draw(hpText);
                }
                else
                {
                    window.draw(gameOverSprite);
                }
            }
        }

        window.display();
    }

    return 0;
}
