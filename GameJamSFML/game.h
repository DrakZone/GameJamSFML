#pragma once
#include <map>
#include "player.h"
#include "bullet.h"
#include "enemy.h"

// A wraper class
class Game
{
public:
	// Constructor / Destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool Running() const;
	const float DeltaTime() const;

	// Function 
	void pollEvents();
	void updateEvents(float deltaTime);
	void updateBullets(float deltaTime);
	void updateEnemies(float deltaTime);
	void updatePoints(int point);
	void update();
	void render();

private:
	// Private Function
	void InitVariable();
	void InitWindow();
	void InitTexture();
	void InitPlayer();
	void InitEnemies();

	// Player
	Player* player;
	
	// Enemy
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	// Windows
	sf::RenderWindow* window;

	// Variables
	sf::Event event;
	sf::Clock clock;
	sf::Font font;
	sf::Text text;
	float deltaTime;
	sf::Vector2f currentPosition;
	sf::Vector2f mousePosition;
	sf::Vector2i mousePositionTemp;
	float directionX;
	float directionY;
	int enemySpawn;
	int totalPoints;
	int attackDmg;
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
};