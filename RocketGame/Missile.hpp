//
//  Missile.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/14/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#ifndef Missile_hpp
#define Missile_hpp

#include <stdio.h>
#include "entity.hpp"

class Missile:public Entity{
public:
    Missile();
    Missile(string);
    void update();
    void update(int, int);
    int misslespeed=15;
    int damage=1;
    bool hit = false;
};

#endif /* Missile_hpp */
