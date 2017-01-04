//#include "stdafx.h"
#include "Monsters.hpp"

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "ResourcePath.hpp"

#include "entity.hpp"


Monsters::Monsters(){
    rect.setSize(sf::Vector2f(23,49)); // may need to change later for collisions. sizes change cause each sprite is differnet size
    rect.setPosition(rand() % 900+1,rand() % 800 + 1);       //random spawn for monsters
    sprite.setPosition(rand() % 900 + 1,rand() % 800+1);
    sprite.setTextureRect(sf::IntRect(28, 230, 23, 49));         //(188,284) Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight)
   	health=3;
    rect.scale(2,2);
    sprite.scale(2,2);
    //sf::Clock moveDino;
    
}
Monsters::Monsters(string typeMon)
{
    if (typeMon == "Yoshi") {
        rect.setSize(sf::Vector2f(23, 49));
        rect.setPosition(rand() % 900 + 1, rand() % 800 + 1);       //random spawn for monsters
        sprite.setPosition(rand() % 900 + 1, rand() % 800 + 1);
        sf::IntRect rectSourceYoshi(86, 40, 23, 49);
        sprite.setTextureRect(rectSourceYoshi);
        health = 5;
        sprite.scale(3,3);
        rect.scale(3,3);
    }
    else if (typeMon == "nyanCat") {
        rect.setSize(sf::Vector2f(98, 60));
        rect.setPosition(rand() % 900 + 1, rand() % 800 + 1);       //random spawn for monsters
        sprite.setPosition(rand() % 900 + 1, rand() % 800 + 1);
        sf::IntRect rectSourceNyan(5, 0, 98, 63);
        sprite.setTextureRect(rectSourceNyan);
        health = 7;
        rect.scale(1.5,1.5);
        sprite.scale(1.5,1.5);
    }
    else if (typeMon == "boss") {
        health = 40;
        speed=15;
        rect.setSize(sf::Vector2f(184, 108)); // may need to change later for collisions. sizes change cause each sprite is differnet size
        sprite.setTextureRect(sf::IntRect(359, 616, 184, 108));         //Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight)
        rect.setPosition(-1000, 0);

    }
    
}

void Monsters::update(int x, int y) {
    sprite.setPosition(rect.getPosition());
    rect.move(x, y);
}

void Monsters::update() {
    sprite.setPosition(rect.getPosition()); //getPosition contains both x and y so no need to split
    rect.move(0, speed);
}

bool Monsters::dead() {
    //    rect.setSize(sf::Vector2f(23,49));
    speed = 0;
    
    return true;
}