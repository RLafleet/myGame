// DangerArea.h
#ifndef DANGER_AREA_H
#define DANGER_AREA_H

#include <SFML/Graphics.hpp>

class DangerArea
{
private:
  sf::Sprite sprite;
  float fireAreaSpawnTimer;
  float fireAreaDespawnInterval;
  float fireAreaSpawnInterval;
  float fireAreaDespawnTimer;
  static sf::Texture fireAreaTexture;
  static sf::Texture electAreaTexture;
  void setTextureFireArea(const sf::Texture &texture);

public:
  DangerArea(float spawnInterval, float despawnInterval);

  static void initFireArea();
  const sf::Sprite &getFireAreaSprite() const;
  void addFireArea(float deltaTime, sf::RenderWindow &window, bool &stateFireArea);
  void moveFireArea(const sf::Vector2f &offset);
  void drawFireArea(sf::RenderWindow &window, const bool &stateFireArea) const;
  bool intersectsFireArea(const sf::Sprite &other) const;
  void addElectArea(float deltaTime, sf::RenderWindow &window, bool &stateElectArea);
};

#endif // DANGER_AREA_H
