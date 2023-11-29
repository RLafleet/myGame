#ifndef FIREBALL_SPAWNER_H
#define FIREBALL_SPAWNER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Fireball.h"

class FireballSpawner
{
  private:
    float fireballSpawnInterval;
    float fireballSpawnTimer;
    std::vector<Fireball> fireballs;

  public:
    FireballSpawner(float spawnInterval);
    void update(float deltaTime, sf::RenderWindow &window, const sf::Texture &sprite, const int &maxFireballs, const sf::Vector2f &playerCenter);
    void draw(sf::RenderWindow &window);
    std::vector<Fireball> &getFireballs();
    // std::vector<BackgroundDecorator> &getDecorations();

  private:
    void addFireball(float deltaTime, sf::RenderWindow &window, const sf::Texture &decorationTexture, const int &maxFireballs, const sf::Vector2f &playerCenter);
};

#endif // FIREBALL_SPAWNER_H
