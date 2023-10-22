#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet();
    Bullet(sf::Texture* texture, float posX, float posY, float directionX, float directionY, float movementSpeed);
    virtual ~Bullet();

    // Accessor
    const sf::FloatRect getBounds() const;

    // Functions
    void update(float deltaTime);
    void render(sf::RenderTarget* target);
private:
    sf::Sprite shape;

    // Private Functions


    // Private Variables
    sf::Vector2f direction;
    float speed;
};