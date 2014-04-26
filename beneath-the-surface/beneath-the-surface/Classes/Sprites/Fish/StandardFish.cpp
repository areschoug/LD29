//
//  StandardFish.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#include "StandardFish.h"
#include "Defines.h"

USING_NS_CC;

StandardFish* StandardFish::create() {
    StandardFish *sprite = new StandardFish();
    if (sprite && sprite->initWithFile("standard_fish_1.png")){
        sprite->setup();
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void StandardFish::setup(){
    Fish::setup();

    
    if (rand() % 2) {
        setPosition(Point(-100, (rand() % 300) + 50));
        _velocity = Point(map(rand() % 10, 0, 10, 30, 60), (rand() % 20) - 10);
        setScaleX(-1);
    } else {
        setPosition(Point(_visibleSize.width + 100, (rand() % 300) + 50));
        _velocity = Point(-map(rand() % 10, 0, 10, 30, 60), (rand() % 20) - 10);
    }
    
    float f = map((rand() % 10), 0, 10, 0.6, 1.0);
    setScaleX(getScaleX() * f);
    setScaleY(f);
    
    _score = 100 * f;
    
    switch (rand() % 4) {
        case 0:
            setColor(Color3B(98,41,168));
            break;
        case 1:
            setColor(Color3B(98,168,41));
            break;
        case 2:
            setColor(Color3B(200,200,0));
            break;
        case 3:            
        default:
            setColor(Color3B(255,200,0));
            break;
    }
    
    
    

    _animatingImages.push_back("standard_fish_1.png");
    _animatingImages.push_back("standard_fish_2.png");
    
    
}