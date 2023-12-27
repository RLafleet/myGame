// Map.h
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "iostream"

class Map
{
private:
  sf::Sprite backgroundRect;

public:
  static sf::Texture gameMapTexture;
  static void gameMapInitialize();
  void gameMapSet(sf::Vector2f pathHero);
  void moveMapTexture(const sf::Vector2f &offset);
  void draw(sf::RenderWindow &window);
  sf::Vector2f getPosition() const;
};

#endif // MAP_H