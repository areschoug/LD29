//
//  Turtle.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#include "Turtle.h"

USING_NS_CC;

Turtle* Turtle::create() {
    Turtle *sprite = new Turtle();
    if (sprite && sprite->initWithFile("turtle_1.png")){
        sprite->setup();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Turtle::setup(){
    Fish::setup();
    
    if (rand() % 2) {
        setPosition(Point(-100, (rand() % 400) + 30));
        _velocity = Point(25, (rand() % 20) - 10);
        setScaleX(-1);
    } else {
        setPosition(Point(_visibleSize.width + 100, (rand() % 400) + 30));
        _velocity = Point(-25, (rand() % 20) - 10);
    }
    
    setColor(Color3B(98,168,41));
    
    _score = 250;
    
    _animatingImages.push_back("turtle_1.png");
    _animatingImages.push_back("turtle_2.png");
    
    
}