#include <SFML/Graphics.hpp>
#include <cassert>
#include "game.h"

// Constructor / Destructor
Game::Game()
{
	this->InitVariable();
	this->InitWindow();
	this->InitPlayer();
	this->InitTexture();
	this->InitEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	// Delete Textures
	for (auto& texture : this->textures)
	{
		delete texture.second;
	}

	// Delete Bullets
	for (auto* texture : this->bullets)
	{
		delete texture;
	}

	// Delete Enemy
	for (auto* texture : this->enemies)
	{
		delete texture;
	}
}

//Accessors
const bool Game::Running() const
{
	return this->window->isOpen();
}

const float Game::DeltaTime() const
{
	return this->deltaTime;
}

// Function
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();
		if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->window->close();
	}

}

void Game::updateEvents(float deltaTime)
{
	//Move Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (this->player->getBounds().left >= 0)
		{
			this->player->Move(-1.f, 0.f, deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (this->player->getBounds().width <= this->window->getSize().x)
		{
			this->player->Move(1.f, 0.f, deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (this->player->getBounds().top >= 0)
		{
			this->player->Move(0.f, -1.f, deltaTime);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (this->player->getBounds().height <= this->window->getSize().y)
		{
			this->player->Move(0.f, 1.f, deltaTime);
		}
	}

	// Mouse Detail
	this->currentPosition = this->player->getPosition();
	this->mousePositionTemp = sf::Mouse::getPosition( * window);
	this->mousePosition = { (float)mousePositionTemp.x, (float)mousePositionTemp.y };

    // now we have both the sprite position and the cursor
    // position lets do the calculation so our sprite will
    // face the position of the mouse
    const float PI = 3.14159265;

    float dx = currentPosition.x - mousePosition.x;
    float dy = currentPosition.y - mousePosition.y;

    float rotation = (atan2(dy, dx)) * 180 / PI -90;

	this->player->Rotate(rotation);

	this->directionY;
	this->directionX;
	
	// Normalization
	float length = sqrt((dx * dx) + (dy * dy));
	if (length != 0)
	{
		this->directionX = -(dx / length);
		this->directionY = -(dy / length);
	}
	else
	{
		this->directionX = -dx;
		this->directionY = -dy;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPosition().x, this->player->getPosition().y, this->directionX, this->directionY, 600.f));
	}
}

void Game::updateBullets(float deltaTime)
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update(deltaTime);

		// Bullet Deleting (Top of Screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			// Deleted Bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			// TO check if Bullet is getting Deleted
			//printf("%f\n", this->bullets.size());
		}
		else if (bullet->getBounds().left + bullet->getBounds().width < 0.f)
		{
			// Deleted Bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			// TO check if Bullet is getting Deleted
			//printf("%f\n", this->bullets.size());
		}
		else if (bullet->getBounds().top > this->window->getSize().y)
		{
			// Deleted Bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			// TO check if Bullet is getting Deleted
			//printf("%f\n", this->bullets.size());
		}
		else if (bullet->getBounds().left > this->window->getSize().x)
		{
			// Deleted Bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			// TO check if Bullet is getting Deleted
			//printf("%f\n", this->bullets.size());
		}
		++counter;
	}
}

void Game::updateEnemies(float deltaTime)
{
	this->spawnTimer += deltaTime;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemySpawn = rand() % 4 + 1;
		switch (this->enemySpawn)
		{
		case 1:
			// Spawn enemies Top
			this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 2.0f, -100.0f, 1));
			break;

		case 2:
			// Spawn enemies Left
			this->enemies.push_back(new Enemy(-100.f, rand() % this->window->getSize().y - 2.0f, 2));
			break;

		case 3:
			// Spawn enemies Bottom
			this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 2.0f, this->window->getSize().y + 100.0f, 3));
			break;

		case 4:
			// Spawn enemies Right
			this->enemies.push_back(new Enemy(this->window->getSize().x + 100.0f, rand() % this->window->getSize().y - 2.0f, 4));
			break;

		default:
			assert(false);
			break;
		}
		// Cool down to spawn enemies
		this->spawnTimer = 0.0f;
	}

	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool isEnemyRemove = false;
		this->enemies[i]->update(deltaTime);

		for (size_t b = 0; b < this->bullets.size() && !isEnemyRemove; ++b)
		{
			if (this->bullets[b]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->enemies[i]->updateHp(this->attackDmg);
				this->bullets.erase(this->bullets.begin() + b);
				if (this->enemies[i]->getHp() == 0)
				{
					// Get Points
					this->updatePoints(this->enemies[i]->getPoint());

					this->enemies.erase(this->enemies.begin() + i);
					isEnemyRemove = true;
				}
			}
		}

		if (!isEnemyRemove)
		{
			if (this->enemies[i]->getspawnPlace() == 1)
			{
				//remove enemy at the bottom of the screen
				if (this->enemies[i]->getBounds().top > this->window->getSize().y)
				{
					this->enemies.erase(this->enemies.begin() + i);
					printf("top Enemy Deleted!\n");
				}
			}
			else if (this->enemies[i]->getspawnPlace() == 2)
			{
				//remove enemy at the right of the screen
				if (this->enemies[i]->getBounds().left > this->window->getSize().x)
				{
					this->enemies.erase(this->enemies.begin() + i);
					printf("left Enemy Deleted!\n");
				}
			}
			else if (this->enemies[i]->getspawnPlace() == 3)
			{
				//remove enemy at the top of the screen
				if (this->enemies[i]->getBounds().height + this->enemies[i]->getBounds().top < 0)
				{
					this->enemies.erase(this->enemies.begin() + i);
					printf("bottom Enemy Deleted!\n");
				}
			}
			else if (this->enemies[i]->getspawnPlace() == 4)
			{
				//remove enemy at the left of the screen
				if (this->enemies[i]->getBounds().width + this->enemies[i]->getBounds().left < 0)
				{
					this->enemies.erase(this->enemies.begin() + i);
					printf("right Enemy Deleted!\n");
				}
			}
		}

		if (this->player->getBounds().intersects(this->enemies[i]->getBounds()))
		{
			this->window->close();
		}

	}
}

void Game::updatePoints(int point)
{
	this->totalPoints += point;
	char buf[512];
	sprintf_s(buf, "Total Points: %i", this->totalPoints);
    this->text.setString(buf);
	this->text.setString(buf);
}

void Game::update()
{
	// Delta Time
	deltaTime = clock.getElapsedTime().asSeconds();
	clock.restart().asSeconds();

	// Call Poll Event
	this->pollEvents();

	this->updateEvents(deltaTime);

	this->player->Update(deltaTime);

	this->updateBullets(deltaTime);

	this->updateEnemies(deltaTime);

}

void Game::render()
{
	this->window->clear();

	// Draw game Objects
	this->player->Render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->window->draw(text);
	this->window->display();
}

// Private Function
void Game::InitVariable()
{
	this->window = nullptr;

}

void Game::InitWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(), "Game Jam!", sf::Style::Fullscreen);

}

void Game::InitTexture()
{
	this->textures["BULLET"] = new sf::Texture();
	if (!this->textures["BULLET"]->loadFromFile("GameJamSFML/Texture/bullets.png"))
	{
		printf("Error: GAME: InitTexture: could not load texture file!\n");
		assert(false);
	}
	if (!this->font.loadFromFile("GameJamSFML/Texture/Asap.ttf"))
	{
		printf("Error: GAME: InitTexture: could not load Font file!\n");
		assert(false);
	}
	this->text.setFont(font);
	this->text.setCharacterSize(50);
	this->text.setFillColor(sf::Color::White);
}

void Game::InitPlayer()
{
	this->player = new Player();

}

void Game::InitEnemies()
{
	this->spawnTimerMax = 1.0f;
	this->spawnTimer = this->spawnTimerMax;
	this->totalPoints = 0;
	this->attackDmg = 1;
}