//
//  Powerup.cpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/20/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#include "Powerup.hpp"
#include "entity.hpp"
Powerup::Powerup(){
    rect.setSize(sf::Vector2f(28,28));
    rect.setPosition(rand()%900+1,0);
//    sprite.setPosition(rand()%1000+1,0);                               //spawns initial missile sprite off screen
    sprite.setTextureRect(sf::IntRect(164, 80, 28, 28));         //Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight) of sprite sheet
    speed=1;
    rect.scale(2,2);
    sprite.scale(2,2);
}
void Powerup::update(){
    
    rect.move(0,speed);                 //rocketship can only shoot up
    sprite.setPosition(rect.getPosition()); //getPosition contains both x and y so no need to split
}