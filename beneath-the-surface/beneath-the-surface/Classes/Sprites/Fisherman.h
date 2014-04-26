//
//  Fisherman.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#ifndef __beneath_the_surface__Fisherman__
#define __beneath_the_surface__Fisherman__

#include "cocos2d.h"

typedef enum {
    BoatDirectionNone,
    BoatDirectionLeft,
    BoatDirectionRight
} BoatDirection;

typedef enum {
    ThrowStateNone,
    ThrowStatePower,
    ThrowStateThrowing,
    ThrowStateThrown,
} ThrowState;

class Fisherman : public cocos2d::Sprite {
  

public:
   
    static Fisherman* create();
    
    void update(float dt);
    void doThrow();
    void doPower();
    
    BoatDirection getBoatDirection();
    void setBoatDirection(BoatDirection boatDirection);
    
    
    
private:
    
    void setup();
    void throwRope();
    void resetRope();
    
    std::vector<cocos2d::Sprite*> _ropeSprites;
    float _power;
    
    
    
    cocos2d::Sprite *_rod;
    BoatDirection _currentBoatDirection;
    
    ThrowState _currentThrowState;
    void setThrowState(ThrowState state);

    
    
};

#endif /* defined(__beneath_the_surface__Fisherman__) */
