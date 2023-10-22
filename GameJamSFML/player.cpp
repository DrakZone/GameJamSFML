#include <SFML/Graphics.hpp>
#include <cassert>
#include "player.h"

// Constructor / Destructor
Player::Player()
{
	this->InitTexture();
	this->InitSprite();
	this->InitVariable();
}

Player::~Player()
{

}

//Accessors
const sf::Vector2f& Player::getPosition() const
{
	return this->sprite.getPosition();
}

sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

// Function
void Player::Update(float deltaTime)
{
	this->updateAttack(deltaTime);
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::Move(const float dirX, const float dirY, float deltaTime)
{
	this->sprite.move(this->Speed * dirX * deltaTime, this->Speed * dirY * deltaTime);
}

void Player::Rotate(float rotation)
{
	this->sprite.setRotation(rotation);
}

void Player::updateAttack(float deltaTime)
{
	if (this->attackCoolDown < this->attackCoolDownMax)
	{
		this->attackCoolDown += deltaTime;
	}

}

const bool Player::canAttack()
{
	if (this->attackCoolDown >= attackCoolDownMax)
	{
		this->attackCoolDown = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

// Private Function
void Player::InitTexture()
{
	// Load a texture from file
	if (!this->texture.loadFromFile("GameJamSFML/Texture/pigeons.png"))
	{
		printf("Error: PLAYER: InitTexture: could not load texture file!\n");
		assert(false);
	}
}

void Player::InitSprite()
{
	// Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	// Resize the sprite
	this->sprite.setOrigin(16.f,16.f);
	this->sprite.scale(2.f, 2.f);
	this->sprite.setPosition(sf::Vector2f(500, 500));
}

void Player::InitVariable()
{
	this->Speed = 350;
	this->attackCoolDownMax = 1.0f;
	this->attackCoolDown = 1.0f;
}
























// Functions
//void Player::Init()
//{
//
//    // Finding The Center
//    auto surface = sf::VideoMode::getDesktopMode();
//    ss_x = surface.width / 2;
//    ss_y = surface.height / 2;
//
//    ss_width = surface.width;
//    ss_height = surface.height;
//
//    Position.x = ss_x;
//    Position.y = ss_y;
//
//    // Player Detail
//    shape.setRadius(radius);
//    shape.setOrigin(shape.getRadius(), shape.getRadius());
//    shape.setPosition(Position);
//    shape.setPointCount(3);
//    shape.setFillColor(sf::Color::Green);
//
//    if (!font.loadFromFile("Asap.ttf"))
//    {
//        printf("No load File");
//    }
//    else
//    {
//        debugManu.setFont(font);
//        debugManu.setFillColor(sf::Color::White);
//        debugManu.setCharacterSize(50);
//        debugManu.setPosition(0, 0);
//    }
//
//}
//
//void Player::Update(sf::RenderWindow& window, float DeltaTime)
//{
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//    {
//        if (shape.getPosition().y - getHitBox >= 0)
//        {
//            Position.y -= Velocity * Speed * DeltaTime;
//        }
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//    {
//        if (shape.getPosition().y + getHitBox <= ss_height)
//        {
//            Position.y += Velocity * Speed * DeltaTime;
//        }
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//    {
//        if (shape.getPosition().x - getHitBox >= 0)
//        {
//            Position.x -= Velocity * Speed * DeltaTime;
//        }
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//    {
//        if (shape.getPosition().x + getHitBox <= ss_width)
//        {
//            Position.x += Velocity * Speed * DeltaTime;
//        }
//    }
//    Shoot(window);
//    shape.setPosition(Position);
//
//}
//
//void Player::Render(sf::RenderTarget& target)
//{
//    target.draw(shape);
//    //Debug
//    char buf[512];
//    sprintf_s(buf, "Position: (x = %f, y = %f)\n", shape.getPosition().x, shape.getPosition().y);
//    debugManu.setString(buf);
//    window.draw(debugManu);
//    window.draw(lines, 2, sf::Lines);
//}
//
//void Player::Shoot(sf::RenderWindow& window)
//{
//    // Mouse Detail
//    currentPos = shape.getPosition();
//    mousePos = sf::Mouse::getPosition(window);
//
//    // now we have both the sprite position and the cursor
//    // position lets do the calculation so our sprite will
//    // face the position of the mouse
//    const float PI = 3.14159265;
//
//    float dx = currentPos.x - mousePos.x;
//    float dy = currentPos.y - mousePos.y;
//
//    float rotation = (atan2(dy, dx)) * 180 / PI + 30;
//
//    shape.setRotation(rotation);
//
//    sf::Vector2f tempMousePos = { (float)mousePos.x, (float)mousePos.y };
//
//    lines[0].position = currentPos;
//    lines[1].position = tempMousePos;
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//    {
//        printf("Shoot!\n");
//    }
//}
//
//sf::Vector2f Player::getPosition()
//{
//    currentPos = shape.getPosition();
//    return currentPos;
//}