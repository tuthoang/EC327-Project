//
//  Monsters.hpp
//  RocketGame
//
//  Created by Timmy Hoang on 4/14/16.
//  Copyright © 2016 Timmy Hoang. All rights reserved.
//

#ifndef Monsters_hpp
#define Monsters_hpp
#include "entity.hpp"
#include <stdio.h>
class Monsters: public Entity{
    
public:
    
    Monsters ();
    Monsters(string);
    void update(int, int);
    void update();
    float speed = 2;
    int health;
    bool dead();
    bool construct = true;
    bool canMoveLeft = false;
    bool canMoveRight = true;
    
};
#endif /* Monsters_hpp */
