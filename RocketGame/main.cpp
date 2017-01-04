#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Rocketship.hpp"
#include "entity.hpp"
#include "Monsters.hpp"
#include "Missile.hpp"
#include "Powerup.hpp"
#include "cScreen.hpp"

#include "screen_0.hpp"
#include "screen_1.hpp"
#include "screen_instructions.hpp"
#include "screen_gameover.hpp"
#include "screen_congrats.hpp"

#include <string>

#include "ResourcePath.hpp"


int main(int argc, char** argv)
{
    //Applications variables
    std::vector<cScreen*> Screens;
    int screen = 0;
    
    //Window creation
    sf::RenderWindow window(sf::VideoMode(2000, 1600), "Rocketship Game", sf::Style::Fullscreen);
//    sf::RenderWindow window(sf::VideoMode(2000, 1600), "Rocketship Game");
   
    //Mouse cursor no more visible
    window.setMouseCursorVisible(false);
    
    //Screens preparations
    screen_0 s0;
    Screens.push_back(&s0);
    screen_instructions sI;
    Screens.push_back(&sI);
    screen_1 s1;
    Screens.push_back(&s1);
    screen_gameover sGameover;
    Screens.push_back(&sGameover);
    screen_congrats sC;
    Screens.push_back(&sC);
    
    //Main loop
    while (screen >= 0)
    {
        screen = Screens[screen]->Run(window);
    }
    
    return EXIT_SUCCESS;
}
