#include <SFML/Graphics.hpp>
#include <time.h>
#include "game.h"



// Player Class
sf::Text debugManu;
sf::Font font;

int main()
{
    // Seed for RNG
    srand(time_t(static_cast<unsigned>(0)));

    // Initialise Game Engine
    Game game;

    //Game Loop
    while (game.Running())
    {
        // Update
        game.update();

        // Render
        game.render();

    }

    return 0;
}
