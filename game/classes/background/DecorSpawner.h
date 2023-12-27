// DecorSpawner.h

#ifndef DECOR_SPAWNER_H
#define DECOR_SPAWNER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "BackgroundDecorator.h"

class DecorSpawner
{
private:
  float decorSpawnInterval;
  float decorSpawnTimer;
  std::vector<BackgroundDecorator> decorations;
  bool hasNearbyDecorations(const sf::Vector2f &position, float radius);

public:
  DecorSpawner(float interval);
  void update(std::string &side, float deltaTime, sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  std::vector<BackgroundDecorator> &getDecorations();

private:
  void addDecoration(const std::string &side, sf::RenderWindow &window);
};

#endif // DECOR_SPAWNER_H
