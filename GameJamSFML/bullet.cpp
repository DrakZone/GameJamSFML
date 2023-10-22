#include <SFML/Graphics.hpp>
#include "bullet.h"

// Constructor / Destructor
Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float directionX, float directionY, float movementSpeed)
{
    shape.setTexture(*texture);

    shape.setPosition(posX, posY);
    shape.setOrigin(8,8);
    direction.x = directionX;
    direction.y = directionY;
    speed = movementSpeed;
}

Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
    return this->shape.getGlobalBounds();
}

// Functions
void Bullet::update(float deltaTime)
{
    // Movement
    this->shape.move(this->speed * this->direction * deltaTime);
}

void Bullet::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
}