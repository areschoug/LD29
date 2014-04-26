//
//  Fish.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#include "Fish.h"

USING_NS_CC;

Fish* Fish::create() {
    Fish *sprite = new Fish();
    if (sprite && sprite->initWithFile("turtle_1.png")){
        sprite->setup();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


void Fish::setup(){

    _updateSpriteTime = 15;
    _visibleSize = Director::getInstance()->getVisibleSize();
}


void Fish::update(float dt){

    if (!_outsideGameBounds) {
        setPosition(getPositionX() + (_velocity.x * dt), getPositionY() + (_velocity.y * dt));

        if ((getPositionX() > (Director::getInstance()->getVisibleSize().width + 100) && _velocity.x > 0) ||
            ((getPositionX() < -100) && _velocity.x < 0)) {
            _outsideGameBounds = true;
        }
        

        
    }
    
    updateAnimation(dt);
}

void Fish::updateAnimation(float dt){
    if (_preventAnimations) return;
    if (_animatingImages.size() > 1) {
        _updateSpriteTicker++;
        if (_updateSpriteTicker > _updateSpriteTime) {
            _updateSpriteTicker -= _updateSpriteTime;
            _currentAnimationPosition++;
            if (_currentAnimationPosition >= _animatingImages.size()) {
                _currentAnimationPosition = 0;
            }
            
            std::string s = _animatingImages.at(_currentAnimationPosition);
            
            setTexture(s);
        }
    }
}

void Fish::setScore(float score){
    _score = score;
}

float Fish::getScore(){
    return _score;
}

cocos2d::Point Fish::getVelocity(){
    return _velocity;
}

void Fish::setVelocity(cocos2d::Point velocity){
    _velocity = velocity;

    
    float deltaY = velocity.y;
    float deltaX = velocity.x;
    float angleInDegrees = atan2(deltaY, deltaX) * 180 / M_PI;
    if (velocity.x < 0) {
        setRotation((angleInDegrees - 180) * -1);
    } else {
        setRotation(angleInDegrees * -1);
    }
}

void Fish::setPreventAnimations(bool preventAnimations){
    _preventAnimations = preventAnimations;
}