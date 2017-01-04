//
//  cScreen.cpp
//  Test
//
//  Created by Scott Hom on 4/17/16.
//  Copyright © 2016 Scott Hom. All rights reserved.
//

#ifndef cScreen_hpp
#define cScreen_hpp


using namespace std;

class cScreen
{
    public :
    virtual int Run (sf::RenderWindow &window) = 0;
};
#endif
