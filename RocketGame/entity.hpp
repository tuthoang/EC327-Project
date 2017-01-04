//
//  entity.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/14/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourcePath.hpp"
#include <cstdlib>

using namespace std;

class Entity{
    
public:
    
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Text text;
    
};

#endif /* entity_hpp */
