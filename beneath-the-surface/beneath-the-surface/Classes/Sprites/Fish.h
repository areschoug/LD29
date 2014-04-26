//
//  Fish.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#ifndef __beneath_the_surface__Fish__
#define __beneath_the_surface__Fish__

#include "cocos2d.h"

class Fish : public cocos2d::Sprite {
    
public:
    static Fish* create();
    void update(float dt);
    void setVelocity(cocos2d::Point velocity);
    cocos2d::Point getVelocity();
    
    float getScore();
    void setScore(float score);
    
protected:
    void setup();
    
    std::vector<std::string> _animatingImages;
    float _updateSpriteTime;
    
    cocos2d::Point _velocity;
    cocos2d::Size _visibleSize;
    float _score;
    
private:
    bool _outsideGameBounds;
    int _currentAnimationPosition;
    float _updateSpriteTicker;
    
};


#endif /* defined(__beneath_the_surface__Fish__) */