#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
private:
  sf::Sprite sprite;
  int hp;
  int ex;
  int damage;

public:
  static sf::Texture demonTexture;
  static sf::Texture demonTexture2;
  static sf::Texture demonTextureBoss;

  static void initializeTexture();
  void initialize(const sf::Vector2f &position);
  void moveTowards(const sf::Vector2f &target, float deltaTime);
  void draw(sf::RenderWindow &window) const;
  sf::Vector2f getPosition() const;
  void move(const sf::Vector2f &offset);
  const sf::Sprite &getSprite() const;
  void repulseFrom(const Enemy &other);

  int getHP() const;
  void setHP(int newHP);
  int getEXP() const;
  void setEXP(int newEXP);
  int getDMG() const;
};

#endif // ENEMY_H
