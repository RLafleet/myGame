#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
private:
  sf::Sprite sprite;
  sf::Texture heroSpDown;
  sf::Texture heroSpUp;
  sf::Texture heroSpRight;
  sf::Texture heroSpLeft;
  void playerTexture(const sf::Texture &texture);
  void setTextureUp();
  void setTextureDown();
  void setTextureLeft();
  void setTextureRight();
  int healthPoints;
  int expPoints;
  int level;

public:
  void playerInitialize();
  void getMovement(std::string &side, sf::Vector2f &movement);
  void draw(sf::RenderWindow &window) const;
  void setPosition(const sf::Vector2f &position);
  sf::Vector2f getPosition() const;
  bool intersects(const sf::Sprite &other) const;
  int getHealthPoints() const;
  void setHealthPoints(int hp);
  int getExpPoints() const;
  void setLevel(int lvl);
  int getLevel() const;
  int getNumberSkills() const;
};

#endif // PLAYER_H
