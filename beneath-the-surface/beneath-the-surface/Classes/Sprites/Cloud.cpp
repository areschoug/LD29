//
//  Cloud.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#include "Cloud.h"

USING_NS_CC;

Cloud* Cloud::create(std::string string) {
    Cloud *sprite = new Cloud();
    if (sprite && sprite->initWithFile(string)){
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Cloud::update(float dt){
    setPosition(getPositionX() + (_velocity.x * dt), getPositionY());
    if (getPositionX() > (Director::getInstance()->getVisibleSize().width + 100) && (_velocity.x > 0)) {
        setPosition(-40, getPositionY());
    } else if((getPositionX() < -100) && _velocity.x < 0){
        setPosition((Director::getInstance()->getVisibleSize().width + 40), getPositionY());
    }
    
}

void Cloud::setVelocity(Point velocity){
    _velocity = velocity;
}