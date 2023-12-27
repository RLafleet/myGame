// MapCreate.h
#ifndef MAP_CREATE_H
#define MAP_CREATE_H

#include "Map.h"
#include <SFML/Graphics.hpp>

class MapCreate
{
private:
  std::vector<Map> gameMapParts;
  void createMapGrid(sf::RenderWindow &window, sf::Vector2f &pathHero);

public:
  std::vector<Map> &getGameMapParts();
  void initMap();
  void drawGameMap(sf::RenderWindow &window);
  void initializeTexture();
};

#endif // MAP_CREATE_H