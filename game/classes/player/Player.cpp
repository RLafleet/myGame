// Player.cpp

#include "Player.h"
#include <iostream>

void Player::playerInitialize()
{
    if (!heroSpDown.loadFromFile("./game/Texture/playerTexture/heroSpDown.png"))
    {
        std::cout << "Failed to load player texture." << std::endl;
    }

    if (!heroSpUp.loadFromFile("./game/Texture/playerTexture/heroSpUp.png"))
    {
        std::cout << "Failed to load player texture." << std::endl;
    }

    if (!heroSpRight.loadFromFile("./game/Texture/playerTexture/heroSpRight.png"))
    {
        std::cout << "Failed to load player texture." << std::endl;
    }

    if (!heroSpLeft.loadFromFile("./game/Texture/playerTexture/heroSpLeft.png"))
    {
        std::cout << "Failed to load player texture." << std::endl;
    }
    playerTexture(heroSpDown);
}

void Player::getMovement(std::string &side, sf::Vector2f &movement)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        setTextureDown();
        side = "down";
        movement.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        setTextureUp();
        side = "up";
        movement.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        setTextureLeft();
        side = "left";
        movement.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        setTextureRight();
        side = "right";
        movement.x += 1.0f;
    }
}

void Player::setTextureUp()
{
    playerTexture(heroSpUp);
}

void Player::setTextureDown()
{
    playerTexture(heroSpDown);
}

void Player::setTextureLeft()
{
    playerTexture(heroSpLeft);
}

void Player::setTextureRight()
{
    playerTexture(heroSpRight);
}

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
