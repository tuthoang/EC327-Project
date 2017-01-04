#ifndef SCREEN_0_HPP
#define SCREEN_0_HPP
#include "ResourcePath.hpp"
#include <iostream>
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>

#endif 

//(?) How does screen 0 get to screen 1 when it breaks out of the render screen loop?
//(?) Also how does excape take screen 1 to an itteration of screen 0 with continue I dont even see

class screen_0 : public cScreen
{
private:

    bool playing;
public:
    screen_0(void);
    virtual int Run(sf::RenderWindow &window);
};

screen_0::screen_0(void)
{

    playing = false;
}

int screen_0::Run(sf::RenderWindow &window)
{
    sf::Event Event;
    bool Running = true;

    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    int menu = 0;

    if (!Font.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        std::cerr << "Error loading verdanab.ttf" << std::endl;
        return (-1);
    }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(50);
    Menu1.setString("Play");
    Menu1.setPosition( window.getSize().x/2, window.getSize().y/3 );
    
    Menu2.setFont(Font);
    Menu2.setCharacterSize(50);
    Menu2.setString("Exit");
    Menu2.setPosition(window.getSize().x/2, 2*window.getSize().y/3 );
    
    Menu3.setFont(Font);
    Menu3.setCharacterSize(50);
    Menu3.setString("Restart");
    Menu3.setPosition(window.getSize().x/2, window.getSize().y/3 );
    

    
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
        //When getting at alpha_max, we stop modifying the sprite

        if (menu == 0)
        {
            Menu1.setColor(sf::Color(255, 0, 0, 255));
            Menu2.setColor(sf::Color(255, 255, 255, 255));
            Menu3.setColor(sf::Color(255, 0, 0, 255));
        }
        else
        {
            Menu1.setColor(sf::Color(255, 255, 255, 255));
            Menu2.setColor(sf::Color(255, 0, 0, 255));
            Menu3.setColor(sf::Color(255, 255, 255, 255));
        }
        
        //Clearing screen
        window.clear();
        //Drawing

        if (playing)
        {
            window.draw(Menu3);
        }
        else
        {
            window.draw(Menu1);
        }
        window.draw(Menu2);
        
        window.display();
    }
    
    //Never reaching this point normally, but just in case, exit the windowlication
    return (-1);
}
