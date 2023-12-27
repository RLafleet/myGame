#ifndef BACKGROUND_DECORATOR_H
#define BACKGROUND_DECORATOR_H

#include <SFML/Graphics.hpp>

class BackgroundDecorator
{
private:
  sf::Sprite decoration;

public:
  static sf::Texture skull1;
  static sf::Texture skull2;
  static sf::Texture skull3;
  static void initializeTexture();
  void draw(sf::RenderWindow &window);
  void initialize(const sf::Vector2f &position);
  void move(const sf::Vector2f &offset);
  const sf::Sprite &getSprite() const;
};

#endif // BACKGROUND_DECORATOR_H
