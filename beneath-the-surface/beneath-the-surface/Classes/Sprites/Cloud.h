//
//  Cloud.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#ifndef __beneath_the_surface__Cloud__
#define __beneath_the_surface__Cloud__

#include "cocos2d.h"

class Cloud : public cocos2d::Sprite {
    
public:
    static Cloud* create(std::string string);
    void update(float dt);
    void setVelocity(cocos2d::Point velocity);
    
private:
    void setup();
    cocos2d::Point _velocity;
    
};
#endif /* defined(__beneath_the_surface__Cloud__) */
