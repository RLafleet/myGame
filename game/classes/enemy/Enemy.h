#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
  private:
    sf::Sprite sprite;

  public:
    void initialize(const sf::Vector2f &position, const sf::Texture &texture);
    void moveTowards(const sf::Vector2f &target, float deltaTime);
    void draw(sf::RenderWindow &window) const;
    sf::Vector2f getPosition() const;
    void move(const sf::Vector2f &offset);
    const sf::Sprite &getSprite() const;
    void repulseFrom(const Enemy &other);
};

#endif // ENEMY_H
