// Player.cpp

#include "Player.h"

void Player::playerTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(875, 450);
}

void Player::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}

void Player::setPosition(const sf::Vector2f &position)
{
    sprite.setPosition(position);
}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

bool Player::intersects(const sf::Sprite &other) const
{
    sf::FloatRect expandedBounds = sprite.getGlobalBounds();

    expandedBounds.left += 60;
    expandedBounds.top += 60;
    expandedBounds.height -= 80;
    expandedBounds.width -= 80;

    return expandedBounds.intersects(other.getGlobalBounds());
}
