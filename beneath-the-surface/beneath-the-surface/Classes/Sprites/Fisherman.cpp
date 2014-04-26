//
//  Fisherman.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#include "Fisherman.h"
#include "Defines.h"

#define kSpeed 200

USING_NS_CC;

Fisherman* Fisherman::create() {
    Fisherman *sprite = new Fisherman();
    if (sprite && sprite->initWithFile("fisherman_none.png")){
        sprite->setup();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


void Fisherman::setup(){

    _rod = Sprite::create("fishing_rod.png");
    this->addChild(_rod,kZRod);
    setThrowState(ThrowStateNone);
    

    
}

void Fisherman::update(float dt){
    
    if (_currentThrowState == ThrowStatePower) {
        _power += dt;
        _power = MIN(_power, 1.0);
//        _rod->setRotation(_power * 8);
    } else {
        _rod->setRotation(0);
    }
    
    if (_currentBoatDirection == BoatDirectionLeft) {
        float distance = -kSpeed * dt;
        setPosition(Point(getPositionX() + distance, getPositionY()));
    } else if (_currentBoatDirection == BoatDirectionRight){
        float distance = kSpeed * dt;
        setPosition(Point(getPositionX() + distance, getPositionY()));
    }
    
    
}

#pragma mark - actions

void Fisherman::doPower(){

    if (_currentThrowState == ThrowStateNone) {
        setThrowState(ThrowStatePower);
    } else {
        setThrowState(ThrowStateNone);
    }
    
}

void Fisherman::doThrow(){
    if (_currentThrowState == ThrowStatePower) {
       setThrowState(ThrowStateThrowing);
    }
}

void Fisherman::throwRope(){

    
    float xDecay = _power * 25;
    float x = xDecay/2;
    float y = 56;
    int i = 0;
    
    _rod->setRotation(0);
    while (y > 14) {
        Sprite *sprite = Sprite::create("blank.png");
        addChild(sprite,99999);
        x += -(xDecay);
        y += -(sprite->getContentSize().height);
        sprite->setScaleX(xDecay/4);
        sprite->setPosition(Point(x , y));
        _ropeSprites.push_back(sprite);
        i++;
    }




    
}

void Fisherman::resetRope(){
    for (int i = 0; i < _ropeSprites.size(); i++) {
        Sprite *s = _ropeSprites.at(i);
        s->getParent()->removeChild(s);
    }
    _ropeSprites.clear();
}



#pragma mark - setters & getters
BoatDirection Fisherman::getBoatDirection(){
    return _currentBoatDirection;
}

void Fisherman::setBoatDirection(BoatDirection boatDirection){
    if (_currentBoatDirection == boatDirection) return;

    _currentBoatDirection = boatDirection;
    setThrowState(ThrowStateNone);
    
    if (_currentBoatDirection == BoatDirectionLeft) {
        setScale(1, 1);
        setRotation(4);
    } else if(_currentBoatDirection == BoatDirectionRight){
        setScale(-1, 1);
        setRotation(-4);
    } else {
        setRotation(0);


    }
    
}

void Fisherman::setThrowState(ThrowState state){

    _currentThrowState = state;
    
    if (state == ThrowStateNone) {
        _rod->setTexture("fishing_rod_normal.png");
        _rod->setPosition(_rod->getContentSize().width + 30, 40);
        resetRope();
    } else if (state == ThrowStatePower){
        _power = 0.1;
        _rod->setTexture("fishing_rod.png");
        _rod->setPosition(_rod->getContentSize().width + 14, 40);
        _rod->setScaleX(1);
    } else if (state == ThrowStateThrowing){
        _rod->setRotation(0);
        _rod->setPosition(14, 40);
        _rod->setScaleX(-1);
        throwRope();
    }
    
    
}



