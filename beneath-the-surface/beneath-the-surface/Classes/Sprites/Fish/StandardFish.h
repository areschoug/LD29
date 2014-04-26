//
//  StandardFish.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#ifndef __beneath_the_surface__StandardFish__
#define __beneath_the_surface__StandardFish__

#include "Fish.h"

class StandardFish : public Fish {
    
public:
    static StandardFish* create();
    
    
private:
    void setup();
    
};


#endif /* defined(__beneath_the_surface__StandardFish__) */
