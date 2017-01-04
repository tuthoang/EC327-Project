//
//  screen_highscores.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/25/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#ifndef screen_highscores_h
#define screen_highscores_h
//
//  screen_highscores.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/24/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//



#include "ResourcePath.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include "cScreen.hpp"
#include <fstream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>


class screen_highscores : public cScreen
{
private:
    int alpha_max;
    int alpha_div;
    bool playing;
public:
    screen_highscores(void);
    virtual int Run(sf::RenderWindow &window);
};

screen_highscores::screen_highscores(void)
{
    alpha_max = 3 * 255;
    alpha_div = 3;
}

int screen_highscores::Run(sf::RenderWindow &window)
{
    sf::Event Event;
    bool Running = true;
    int theline;
    int alpha = 0;
    sf::Font Font;
    sf::Text HIGHSCORES;
    sf::Text H_1;
    sf::Text H_2;
    sf::Text H_3;
    sf::Text H_4;
    sf::Text H_5;

    int menu = 0;
    
    
    
    ifstream scores;
    scores.open("scores.txt");
    vector<int> high_scores;
    while (scores>>theline)  // read a line
        high_scores.push_back(theline);  // put it in the vector board
    
    scores.close();  //close file
    
    sort (high_scores.begin(), high_scores.end());

    
    if (!Font.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        std::cerr << "Error loading verdanab.ttf" << std::endl;
        return (-1);
    }
    
    HIGHSCORES.setFont(Font);
    HIGHSCORES.setCharacterSize(200);
    HIGHSCORES.setString("HIGHSCORES");
    HIGHSCORES.setPosition(0, 0 );
    HIGHSCORES.setColor(sf::Color::Blue);
    H_1.setFont(Font);
    H_1.setCharacterSize(200);
    H_1.setString(to_string(high_scores[high_scores.size()-1]));
    H_1.setPosition(0, 100 );
    H_1.setColor(sf::Color::Blue);

    H_2.setFont(Font);
    H_2.setCharacterSize(200);
    H_2.setString(to_string(high_scores[high_scores.size()-2]));
    H_2.setPosition(0, 100 );
    H_2.setColor(sf::Color::Blue);
    
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
                        {

                            return (3);
                            break;
                        }
 
                    default:
                        break;
                }
            }
        }
        //When getting at alpha_max, we stop modifying the sprite
        if (alpha<alpha_max)
        {
            alpha++;
        }
//        for (int i=0;i<high_scores.size();i++){
//            cout<<high_scores[i]<<endl;
//        }
    //    cout<<high_scores[-1];
        //Clearing screen
        window.clear();
        //Drawing
        window.draw(HIGHSCORES);
        window.draw(H_1);
        window.draw(H_2);
        window.display();
    }
    
    //Never reaching this point normally, but just in case, exit the windowlication
    return (-1);
}



#endif /* screen_highscores_h */
