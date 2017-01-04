//
//  Rocketship.cpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/13/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "ResourcePath.hpp"

#include "entity.hpp"
#include "Rocketship.hpp"

Rocketship::Rocketship(){
    rect.setSize(sf::Vector2f(100,122)); // may need to change later for collisions. sizes change cause each sprite is differnet size
    rect.setPosition(500,400);
    sprite.setPosition(500,400);
    sprite.setTextureRect(sf::IntRect(0, 0, 100, 122));         //Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight)
    health=3;
    speed=5;
}

void Rocketship::update(){
    sprite.setPosition(rect.getPosition()); //getPosition contains both x and y so no need to split 
}

void Rocketship::updateSpeed(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (speed==20)
            speed=20;
        else
            speed++;
        
    }
    else
        speed=10;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // left key is pressed: move our character
        rect.move(speed, 0);
        sprite.setTextureRect(sf::IntRect(314, 154, 66, 154));
        rect.setSize(sf::Vector2f(66,154));                                 //rect same width and height as sprite
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // left key is pressed: move our character
        rect.move(-speed, 0);
        sprite.setTextureRect(sf::IntRect(116, 154, 66, 154));
        rect.setSize(sf::Vector2f(66,154));

        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // left key is pressed: move our character
        rect.move(0, -speed);
        sprite.setTextureRect(sf::IntRect(0, 154, 100, 154));
        rect.setSize(sf::Vector2f(100,154));
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // left key is pressed: move our character
        rect.move(0, speed);
        sprite.setTextureRect(sf::IntRect(0, 154, 100, 154));
        rect.setSize(sf::Vector2f(100,154));
    }
}
