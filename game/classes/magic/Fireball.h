#ifndef FIREBALL_H
#define FIREBALL_H

#include <SFML/Graphics.hpp>

class Fireball
{
private:
  sf::Sprite sprite;
  float orbitRadius;
  float angle;

public:
  Fireball(const sf::Texture &texture, float radius, float initialAngle);
  void initialize(sf::Vector2f center, float deltaTime);
  const sf::Sprite &getSprite() const;
  void draw(sf::RenderWindow &window) const;
  float getAngle() const;
};

#endif // FIREBALL_H
