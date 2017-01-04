//
//  screen_instructions.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/24/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#ifndef screen_instructions_h
#define screen_instructions_h

#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>

//(?) How does screen 0 get to screen 1 when it breaks out of the render screen loop?
//(?) Also how does excape take screen 1 to an itteration of screen 0 with continue I dont even see

class screen_instructions : public cScreen
{
private:

//    bool playing;
public:
    virtual int Run(sf::RenderWindow &window);
};



int screen_instructions::Run(sf::RenderWindow &window)
{
    sf::Event Event;
    bool Running = true;
    
    int alpha = 0;
    sf::Font Font;
    sf::Text instruction1;
    sf::Text instruction2;
    sf::Text instruction3;
    sf::Text instruction4;
    sf::Text instruction5;
    int menu = 0;
    
    
    
    if (!Font.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        std::cerr << "Error loading verdanab.ttf" << std::endl;
        return (-1);
    }
    instruction1.setFont(Font);
    instruction1.setCharacterSize(50);
    instruction1.setString("Press Spacebar to Shoot");
    instruction1.setPosition( window.getSize().x/2, 3*window.getSize().y/7 );
    instruction1.setColor(sf::Color::White);
    instruction2.setFont(Font);
    instruction2.setCharacterSize(50);
    instruction2.setString("Use arrow keys to move");
    instruction2.setPosition(window.getSize().x/2, 4*window.getSize().y/7 );
    instruction2.setColor(sf::Color::White);

    instruction3.setFont(Font);
    instruction3.setCharacterSize(50);
    instruction3.setString("Press enter to start the game");
    instruction3.setPosition(window.getSize().x/2, 5*window.getSize().y/7 );
    instruction3.setColor(sf::Color::White);
    
    instruction4.setFont(Font);
    instruction4.setCharacterSize(50);
    instruction4.setString("Press escape to exit the game");
    instruction4.setPosition(window.getSize().x/2, 6*window.getSize().y/7 );
    instruction4.setColor(sf::Color::White);

    instruction5.setFont(Font);
    instruction5.setCharacterSize(50);
    instruction5.setString("Do not let the monsters get past you!");
    instruction5.setPosition(0, window.getSize().y/7 );
    instruction5.setColor(sf::Color::White);
    while (Running)
    {
        //Verifying events
        while (window.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                        
                    case sf::Keyboard::Return:
                        
                        //Let's get play !
                        return (2);
                        break;
                    case sf::Keyboard::Escape:
                        //Let's get work...
                        return (-1);
                        break;
                    default:
                        break;
                }
            }
        }

        
        //Clearing screen
        window.clear();
        //Drawing
        window.draw(instruction1);
        window.draw(instruction2);
        window.draw(instruction3);
        window.draw(instruction4);
        window.draw(instruction5);
        window.display();
    }
    
    //Never reaching this point normally, but just in case, exit the windowlication
    return (-1);
}

#endif /* screen_instructions_h */
