//
//  screen_gameover.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/24/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#ifndef screen_gameover_h
#define screen_gameover_h


#include "ResourcePath.hpp"
#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>


class screen_gameover : public cScreen
{
private:

    bool playing;
public:
    virtual int Run(sf::RenderWindow &window);
};


int screen_gameover::Run(sf::RenderWindow &window)
{
    sf::Event Event;
    bool Running = true;
    
    int alpha = 0;
    sf::Font Font;
    sf::Text Gameover;
    sf::Text instruction1;
    sf::Text instruction2;
    int menu = 0;
    
    
    
    
    
    
    
    if (!Font.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        std::cerr << "Error loading verdanab.ttf" << std::endl;
        return (-1);
    }
    Gameover.setFont(Font);
    Gameover.setCharacterSize(200);
    Gameover.setString("GAMEOVER");
    Gameover.setPosition( window.getSize().x/2-500, 0 );
    Gameover.setColor(sf::Color::Yellow);
    
    instruction2.setFont(Font);
    instruction2.setCharacterSize(50);
    instruction2.setString("Exit");
    instruction2.setPosition(window.getSize().x/2, 2*window.getSize().y/3 );
    
    instruction1.setFont(Font);
    instruction1.setCharacterSize(50);
    instruction1.setString("Continue");
    instruction1.setPosition(window.getSize().x/2, window.getSize().y/3 );
    
    
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
                    case sf::Keyboard::Up:
                        menu = 0;
                        break;
                    case sf::Keyboard::Down:
                        menu = 1;
                        break;
                    case sf::Keyboard::Return:
                        if (menu == 0)
                        {
                            //Let's get play !
                            playing = true;
                            return (1);
                        }
                        else
                        {
                            //Let's get work...
                            return (-1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        if (menu == 0)
        {
       //     Menu1.setColor(sf::Color(255, 0, 0, 255));
            instruction1.setColor(sf::Color(255, 0, 0, 255));
            instruction2.setColor(sf::Color(255, 255, 255, 255));

        }
        else
        {
        //    Menu1.setColor(sf::Color(255, 255, 255, 255));
            instruction1.setColor(sf::Color(255, 255, 255, 255));
            instruction2.setColor(sf::Color(255, 0, 0, 255));

        }
        
        //Clearing screen
        window.clear();
        //Drawing
        window.draw(Gameover);
        window.draw(instruction1);
        window.draw(instruction2);
        window.display();
    }
    
    //Never reaching this point normally, but just in case, exit the windowlication
    return (-1);
}

#endif /* screen_instructions_h */
