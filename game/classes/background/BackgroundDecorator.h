#ifndef BACKGROUND_DECORATOR_H
#define BACKGROUND_DECORATOR_H

#include <SFML/Graphics.hpp>

class BackgroundDecorator
{
private:
  sf::Sprite decoration;

public:
  static sf::Texture BushTexture;
  static void initializeTexture();
  void draw(sf::RenderWindow &window) const;
  void initialize(const sf::Vector2f &position, const sf::Texture &texture);
  void move(const sf::Vector2f &offset);
};

#endif // BACKGROUND_DECORATOR_H
