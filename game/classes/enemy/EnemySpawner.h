#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

class EnemySpawner
{
private:
  float spawnInterval;
  float spawnTimer;
  std::vector<Enemy> enemies;

public:
  EnemySpawner(float interval);
  void update(float deltaTime, sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  std::vector<Enemy> &getEnemies();

private:
  std::array<int, 4> countEnemiesByRegion(const sf::RenderWindow &window) const;
  void spawnEnemy(sf::RenderWindow &window);
};

#endif // ENEMY_SPAWNER_H
