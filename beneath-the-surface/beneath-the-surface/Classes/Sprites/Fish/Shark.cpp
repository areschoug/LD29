//
//  Shark.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#include "Shark.h"

USING_NS_CC;

Shark* Shark::create() {
    Shark *sprite = new Shark();
    if (sprite && sprite->initWithFile("shark_1.png")){
        sprite->setup();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Shark::setup(){
    Fish::setup();
    
    if (rand() % 2) {
        setPosition(Point(-100, (rand() % 200) + 30));
        setVelocity(Point(55, (rand() % 20) - 10));
        setScaleX(-1);
    } else {
        setPosition(Point(_visibleSize.width + 100, (rand() % 200) + 30));
        setVelocity(Point(-65, (rand() % 20) - 10));
    }
    
    setColor(Color3B(60,60,60));
    
    _score = 250;
    
    _animatingImages.push_back("shark_1.png");
    _animatingImages.push_back("shark_2.png");
    
    
}

void Shark::resetAnimation(){
    std::string s = _animatingImages.at(0);
    setTexture(s);
}

void Shark::update(float dt){
    updateAnimation(dt);
}