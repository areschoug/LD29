//
//  Shark.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#ifndef __beneath_the_surface__Shark__
#define __beneath_the_surface__Shark__

#include "Fish.h"

class Shark : public Fish {
    
public:
    static Shark* create();
    void update(float dt);
    void resetAnimation();
    
private:
    void setup();
    
};
#endif /* defined(__beneath_the_surface__Shark__) */
