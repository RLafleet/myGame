#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
  private:
    sf::Sprite sprite;

  public:
    void playerTexture(const sf::Texture &texture);
    void draw(sf::RenderWindow &window) const;
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition() const;
    bool intersects(const sf::Sprite &other) const;
};

#endif // PLAYER_H
