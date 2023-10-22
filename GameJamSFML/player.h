#pragma once
#include <SFML/Graphics.hpp>


class Player
{
public:

    // Constructor / Destructor
    Player();
    virtual ~Player();

    // Accessor
    const sf::Vector2f& getPosition() const;
    sf::FloatRect getBounds() const;

    // Functions
    void Update(float deltaTime);
    void Render(sf::RenderTarget& target);

    void Move(const float dirX, const float dirY, float deltaTime);
    void Rotate(float rotation);
    void updateAttack(float deltaTime);
    const bool canAttack();


private:
    sf::Sprite sprite;
    sf::Texture texture;

    // Private Functions
    void InitTexture();
    void InitSprite();
    void InitVariable();

    // Variables
    float Speed;
    float attackCoolDown;
    float attackCoolDownMax;
};



//class Player
//{
//public:
//
//    // Constructor / Destructor
//    Player();
//    virtual ~Player();
//
//    // Functions
//    void Init();
//    void Update(sf::RenderWindow& window, float DeltaTime);
//    void Render(sf::RenderTarget& target);
//    void Shoot(sf::RenderWindow& window);
//    sf::Vector2f getPosition();
//
//    sf::CircleShape shape;
//    sf::Vertex lines[2];
//
//private:
//    signed int ss_x, ss_y;
//    unsigned int ss_speed;
//    int ss_width, ss_height;
//    float radius = 40.0f;
//    int Speed = 200;
//    float getHitBox = 40.0f;
//    sf::Vector2f Position;
//    sf::Vector2f currentPos;
//    sf::Vector2i mousePos;
//    float Velocity = 1;
//    float x = 0;
//};