#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	// Constructor / Destructor
	Enemy(float posX, float posY, int spawn_Place);
	virtual ~Enemy();

	//Accessors
	sf::FloatRect getBounds() const;
	const int getspawnPlace() const;
	const int getType() const;
	const int getPoint() const;
	const int getHp() const;

	// Functions
	void updateHp(int damage);
	void update(float deltaTime);
	void render(sf::RenderTarget* target);

private:
	sf::Sprite shape;
	sf::Texture texture;

	// Private Function
	void InitTexture();
	void InitSprite();
	void InitVariables();
	void InitShapes();

	// Private Variables
	sf::Vector2f direction;
	int spawnPlace;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;
};