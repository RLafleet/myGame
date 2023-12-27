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
  void update(float deltaTime, sf::RenderWindow &window, int levelPlayer, const sf::Vector2f &playerCenter);
  void draw(sf::RenderWindow &window);
  std::vector<Fireball> &getFireballs();

private:
  void addFireball(float deltaTime, sf::RenderWindow &window, int levelPlayer, const sf::Vector2f &playerCenter, int &i);
};

#endif // FIREBALL_SPAWNER_H
