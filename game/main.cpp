#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>

sf::Vector2f normalize(const sf::Vector2f &vector);

class Player
{
  private:
    sf::Sprite sprite;

  public:
    void playerTexture(const sf::Texture &texture)
    {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setPosition(875, 450);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(sprite);
    }

    void setPosition(const sf::Vector2f &position)
    {
        sprite.setPosition(position);
    }

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    bool intersects(const sf::Sprite &other) const
    {
        sf::FloatRect expandedBounds = sprite.getGlobalBounds();

        expandedBounds.left += 60;
        expandedBounds.top += 60;
        expandedBounds.height -= 80;
        expandedBounds.width -= 80;

        return expandedBounds.intersects(other.getGlobalBounds());
    }
};

class Fireball
{
  private:
    sf::Sprite sprite;
    float orbitRadius;
    float angle;

  public:
    Fireball(const sf::Texture &texture, float radius, float initialAngle) : orbitRadius(radius), angle(initialAngle)
    {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    }

    void update(sf::Vector2f center, float deltaTime)
    {
        const float orbitSpeed = 110.0f;
        angle += orbitSpeed * deltaTime;

        float radAngle = angle * (3.14159265f / 180.0f);

        sprite.setPosition(
            center.x + orbitRadius * cos(radAngle),
            center.y + orbitRadius * sin(radAngle));
    }

    const sf::Sprite &getSprite() const
    {
        return sprite;
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(sprite);
    }

    float getAngle() const
    {
        return angle;
    }
};

class Map
{
  private:
    sf::RectangleShape backgroundRect; // Replace sf::Sprite with sf::RectangleShape

  public:
    Map()
    {
        backgroundRect.setSize(sf::Vector2f(1920.0f, 1080.0f)); // Adjust the size as needed
        backgroundRect.setFillColor(sf::Color::Black);
        backgroundRect.setOrigin(1920.0f / 2.0f, 1080.0f / 2.0f);
        backgroundRect.setPosition(1000, 500);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(backgroundRect);
    }
};

class Enemy
{
  private:
    sf::Sprite sprite;

  public:
    void initialize(const sf::Vector2f &position, const sf::Texture &texture)
    {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        sprite.setPosition(position);
    }

    void moveTowards(const sf::Vector2f &target, float deltaTime)
    {
        sf::Vector2f direction = normalize(target - sprite.getPosition());
        sprite.move(direction * 100.0f * deltaTime);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(sprite);
    }

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    void move(const sf::Vector2f &offset)
    {
        sprite.move(offset);
    }

    const sf::Sprite &getSprite() const
    {
        return sprite;
    }

    void repulseFrom(const Enemy &other)
    {
        const float REPULSION_DISTANCE = 70.0f; // Set this to the minimum allowed distance between enemies
        sf::Vector2f delta = sprite.getPosition() - other.sprite.getPosition();
        float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        if (distance > 0 && distance < REPULSION_DISTANCE)
        {
            sf::Vector2f repulsionDir = normalize(delta);
            float repulsionMagnitude = REPULSION_DISTANCE - distance;

            sprite.move(repulsionDir * repulsionMagnitude);
        }
    }
};

class EnemySpawner
{
  private:
    float spawnInterval;
    float spawnTimer;
    std::vector<Enemy> enemies;

  public:
    EnemySpawner(float interval) : spawnInterval(interval), spawnTimer(interval) {}

    void update(float deltaTime, sf::RenderWindow &window, const sf::Texture &demonTexture)
    {
        spawnTimer -= deltaTime;
        if (spawnTimer <= 0.0f)
        {
            spawnEnemy(window, demonTexture);
            spawnTimer = spawnInterval;
        }
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &enemy : enemies)
        {
            enemy.draw(window);
        }
    }

    std::vector<Enemy> &getEnemies()
    {
        return enemies;
    }

  private:
    std::array<int, 4> countEnemiesByRegion(const sf::RenderWindow &window) const
    {
        std::array<int, 4> counts = {0, 0, 0, 0}; // Order: [above, below, left, right]
        for (const auto &enemy : enemies)
        {
            if (enemy.getPosition().y - 200 < window.getSize().y / 2)
            {
                counts[0]++;
            }
            if (enemy.getPosition().y + 200 > window.getSize().y / 2)
            {
                counts[1]++;
            }
            if (enemy.getPosition().x - 200 < window.getSize().x / 2)
            {
                counts[2]++;
            }
            if (enemy.getPosition().x + 200 > window.getSize().x / 2)
            {
                counts[3]++;
            }
        }
        return counts;
    }

    void spawnEnemy(sf::RenderWindow &window, const sf::Texture &demonTexture)
    {
        float randomX = 0.0f;
        float randomY = 0.0f;
        auto counts = countEnemiesByRegion(window);

        bool spawnAbove = counts[0] < 11;
        bool spawnBelow = counts[1] < 11;
        bool spawnLeft = counts[2] < 11;
        bool spawnRight = counts[3] < 11;

        if (spawnAbove && spawnBelow && spawnLeft && spawnRight)
        {

            if (std::rand() % 2 == 0)
            {
                randomX = static_cast<float>(std::rand() % 1920);
                randomY = (std::rand() % 2 == 0) ? 0.0f : 1080.0f;
            }
            else
            {
                randomX = (std::rand() % 2 == 0) ? 0.0f : 1920.0f;
                randomY = static_cast<float>(std::rand() % 1080);
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

        Enemy newEnemy;
        newEnemy.initialize(sf::Vector2f(randomX, randomY), demonTexture);
        enemies.push_back(newEnemy);
    }
};

class BackgroundDecorator
{
  private:
    sf::Sprite decoration;

  public:
    void draw(sf::RenderWindow &window) const
    {
        window.draw(decoration);
    }

    void initialize(const sf::Vector2f &position, const sf::Texture &texture)
    {
        decoration.setTexture(texture);
        decoration.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
        decoration.setPosition(position);
    }

    void move(const sf::Vector2f &offset)
    {
        decoration.move(offset);
    }
};

class DecorSpawner
{
  private:
    float decorSpawnInterval;
    float decorSpawnTimer;
    std::vector<BackgroundDecorator> decorations;

  public:
    DecorSpawner(float interval) : decorSpawnInterval(interval), decorSpawnTimer(interval) {}

    void update(std::string side, float deltaTime, sf::RenderWindow &window, const sf::Texture &decorationTexture)
    {
        decorSpawnTimer -= deltaTime;
        if (decorSpawnTimer <= 0.0f)
        {
            addDecoration(side, window, decorationTexture);
            decorSpawnTimer = decorSpawnInterval;
        }
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &decoration : decorations)
        {
            decoration.draw(window);
        }
    }

    std::vector<BackgroundDecorator> &getDecorations()
    {
        return decorations;
    }

  private:
    void addDecoration(const std::string &side, sf::RenderWindow &window, const sf::Texture &decorationTexture)
    {
        int randomY = 100;
        int randomX = 100;

        if (side == "down")
        {
            randomY = static_cast<int>(window.getSize().y + 400);
            randomX = static_cast<int>(std::rand() % 1920);
        }
        if (side == "up")
        {
            randomY = static_cast<int>(-400);
            randomX = static_cast<int>(std::rand() % 1920);
        }
        if (side == "left")
        {
            randomY = static_cast<int>(std::rand() % 1920);
            randomX = static_cast<int>(-400);
        }
        if (side == "right")
        {
            randomY = static_cast<int>(std::rand() % 1920);
            randomX = static_cast<int>(window.getSize().x + 400);
        }
        BackgroundDecorator newDecoration;
        newDecoration.initialize(sf::Vector2f(randomX, randomY), decorationTexture);
        decorations.push_back(newDecoration);
    }
};

sf::Vector2f normalize(const sf::Vector2f &vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        return sf::Vector2f(vector.x / length, vector.y / length);
    }
    return vector;
}

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

    const float ENEMY_SPAWN_INTERVAL = 0.7f;
    float enemySpawnTimer = ENEMY_SPAWN_INTERVAL;

    EnemySpawner spawner(ENEMY_SPAWN_INTERVAL);

    sf::Texture demonTexture;
    if (!demonTexture.loadFromFile("./game/Texture/enemyTexture/demon.png"))
    {
        std::cout << "Failed to load demon texture." << std::endl;
    }

    // fireballs
    const int maxFireballs = 7;
    const float spawnInterval = 1.4f;
    float spawnTimer = 0.0f;
    const float orbitRadius = 240.0f;
    std::vector<Fireball> fireballs;
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
    const float DECORATION_SPAWN_INTERVAL = 1.8f;
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

        //Fireballs spawn
        if (spawnTimer >= spawnInterval && fireballs.size() < maxFireballs * 2)
        {
            float angle = fireballs.empty() ? 0.0f : fireballs.back().getAngle() + (360.0f / maxFireballs);
            fireballs.emplace_back(fireballTexture, orbitRadius, angle);
            spawnTimer = 0.0f;
        }

        //enemies spawn
        auto &enemies = spawner.getEnemies();
        spawner.update(deltaTime, window, demonTexture);

        //Fireballs movement around Player
        sf::Vector2f playerCenter = player.getPosition();
        for (auto &fireball : fireballs)
        {
            fireball.update(playerCenter, deltaTime);
        }

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
            sf::Vector2f playerPosition = player.getPosition();
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

        sf::Vector2f playerPosition(window.getSize().x / 2, window.getSize().y / 2);

        //Draws
        window.clear();
        gameMap.draw(window);
        player.draw(window);

        //These part of code i should rewrite. For these i must add class fireballSpawner and rewrite class filreball
        for (const auto &fireball : fireballs)
        {
            fireball.draw(window);
        }
        //

        spawner.draw(window);
        decorationSpawner.draw(window);

        window.display();
    }

    return 0;
}
