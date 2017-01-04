//
//  Rocketship.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/13/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#ifndef Rocketship_hpp
#define Rocketship_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

#include "entity.hpp"
using namespace std;
class Rocketship: public Entity{
    
public:
    
    Rocketship();
    void update();
    void updateSpeed();
    int speed;
    int health;
    
    
};
#endif /* Rocketship_hpp */
