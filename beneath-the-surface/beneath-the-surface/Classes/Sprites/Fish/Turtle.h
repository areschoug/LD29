//
//  Turtle.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#ifndef __beneath_the_surface__Turtle__
#define __beneath_the_surface__Turtle__

#include "Fish.h"

class Turtle : public Fish {
    
public:
    static Turtle* create();
    
    
private:
    void setup();
    
};
#endif /* defined(__beneath_the_surface__Turtle__) */
