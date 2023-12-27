#ifndef FIREBALL_H
#define FIREBALL_H

#include <SFML/Graphics.hpp>

class Fireball
{
private:
  sf::Sprite sprite;
  float orbitRadius;
  float angle;
  int damage;

public:
  static sf::Texture fireballTexture;
  Fireball(float radius, float initialAngle, int damage);
  static void initializeTexture();
  void initialize(sf::Vector2f center, float deltaTime);
  const sf::Sprite &getSprite() const;
  void draw(sf::RenderWindow &window) const;
  float getAngle() const;
  int getDamage() const;
};

#endif // FIREBALL_H
