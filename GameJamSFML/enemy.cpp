#include <SFML/Graphics.hpp>
#include <cassert>
#include "enemy.h"

// Constructor / Destructor
Enemy::Enemy(float posX, float posY, int spawn_Place)
{
	// Initialising
    this->InitVariables();
	this->InitTexture();
	this->InitSprite();
    this->InitShapes();

	// Enemy Placement
	this->shape.setPosition(posX, posY);
	this->spawnPlace = spawn_Place;
	if (spawnPlace == 1)
	{
		this->shape.setRotation(180);
	}
	else if (spawnPlace == 2)
	{
		this->shape.setRotation(90);
	}
	else if (spawnPlace == 3)
	{
		this->shape.setRotation(0);
	}
	else if (spawnPlace == 4)
	{
		this->shape.setRotation(270);
	}
}

Enemy::~Enemy()
{

}

//Accessors
sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int Enemy::getspawnPlace() const
{
	return this->spawnPlace;
}

const int Enemy::getType() const
{
	return this->type;
}

const int Enemy::getPoint() const
{
	return this->points;
}

const int Enemy::getHp() const
{
	return this->hp;
}


void Enemy::updateHp(int damage)
{
	this->hp = this->hp - damage;
}

// Functions
void Enemy::update(float deltaTime)
{
	if (spawnPlace == 1)
	{
		this->shape.move(0 * speed *deltaTime, 1 * speed * deltaTime);
	}
	else if (spawnPlace == 2)
	{
		this->shape.move(1 * speed * deltaTime,0 * speed * deltaTime);
	}
	else if (spawnPlace == 3)
	{
		this->shape.move(0 * speed * deltaTime, -1 * speed * deltaTime);
	}
	else if (spawnPlace == 4)
	{
		this->shape.move(-1 * speed * deltaTime, 0 * speed * deltaTime);
	}
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Enemy::InitTexture()
{
	// Load a texture from file
	if (!this->texture.loadFromFile("GameJamSFML/Texture/skeleton-move_0.png"))
	{
		printf("Error: ENEMY: InitTexture: could not load texture file!\n");
		assert(false);
	}

}

void Enemy::InitSprite()
{
	// Set the texture to the sprite
	this->shape.setTexture(this->texture);

}

void Enemy::InitVariables()
{
	this->spawnPlace = 0;
	this->type = 0;
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->damage = 1;
	this->points = 1;
	this->speed = 200;
}

void Enemy::InitShapes()
{
	this->type = rand() % 4 + 1;
	switch (this->type)
	{
	case 1:
		// Type 1 Enemy
		this->hpMax = 2;
		this->hp = 2;
		this->speed = 200;
		this->points = 1;
		// Resize the sprite
		this->shape.scale(0.5f, 0.5f);
		break;

	case 2:
		// Type 2 Enemy
		this->hpMax = 1;
		this->hp = 1;
		this->speed = 600;
		this->points = 5;
		// Resize the sprite
		this->shape.scale(0.2f, 0.2f);
		break;

	case 3:
		// Type 3 Enemy
		this->hpMax = 5;
		this->hp = 5;
		this->speed = 100;
		this->points = 3;
		// Resize the sprite
		this->shape.scale(1.5f, 1.5f);
		break;

	case 4:
		// Type 4 Enemy
		this->hpMax = 10;
		this->hp = 10;
		this->speed = 90;
		this->points = 3;
		// Resize the sprite
		this->shape.scale(1.0f, 1.0f);
		break;

	default:
		assert(false);
		break;
	}
}