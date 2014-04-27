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
    void hurtUpdate(float dt);
    void resetAnimation();
    void setHurt();
    void removeHurt();
    bool getHurt();
    void setQuiet(bool quiet);
private:
    void setup();
    
    float _hurtTicker;
    float _hurtBlinkTicker;
    
    bool _hurt;
    bool _quiet;
    
};
#endif /* defined(__beneath_the_surface__Shark__) */
