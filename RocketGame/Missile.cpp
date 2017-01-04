//
//  Gunfire.cpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/14/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#include "Missile.hpp"
#include "entity.hpp"
Missile::Missile(){
    rect.setSize(sf::Vector2f(10,10));
    rect.setPosition(500,400);
    sprite.setPosition(1100,400);                               //spawns initial missile sprite off screen
    sprite.setTextureRect(sf::IntRect(155, 83, 15, 43));         //Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight) of sprite sheet
}
Missile::Missile(string missileType)
{
    rect.setSize(sf::Vector2f(10, 10));
    rect.setPosition(500, 400);
    sprite.setPosition(1100, 400);                               //spawns initial missile sprite off screen
    sprite.setTextureRect(sf::IntRect(0,0, 25, 43));
}
void Missile::update(){
    
    rect.move(0,-misslespeed);                 //rocketship can only shoot up
    sprite.setPosition(rect.getPosition()); //getPosition contains both x and y so no need to split
}
void Missile::update(int x, int y) {
    rect.move(x, y);
    sprite.setPosition(rect.getPosition());
    
}