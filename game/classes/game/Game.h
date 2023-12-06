#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
private:
  void windowClose(sf::RenderWindow &window) const;

public:
  void gameKeys(sf::RenderWindow &window);
};

#endif // ENEMY_H
