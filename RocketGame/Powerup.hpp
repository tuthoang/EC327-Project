//
//  Powerup.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/20/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#ifndef Powerup_hpp
#define Powerup_hpp

#include <stdio.h>

#endif /* Powerup_hpp */
#include "entity.hpp"

class Powerup:public Entity{
public:
    Powerup();
    void update();
    int speed;
};