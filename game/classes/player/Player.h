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

public:
  void playerInitialize();
  void getMovement(std::string &side, sf::Vector2f &movement);
  void draw(sf::RenderWindow &window) const;
  void setPosition(const sf::Vector2f &position);
  sf::Vector2f getPosition() const;
  bool intersects(const sf::Sprite &other) const;
};

#endif // PLAYER_H
