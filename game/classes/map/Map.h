#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map
{
private:
  sf::RectangleShape backgroundRect;

public:
  Map();
  void draw(sf::RenderWindow &window);
};

#endif // MAP_H
