//
//  GameScene.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#ifndef __beneath_the_surface__GameScene__
#define __beneath_the_surface__GameScene__

#include "cocos2d.h"
#include "Fisherman.h"



class GameScene : public cocos2d::Layer
{
    
public:

    static cocos2d::Scene* createScene();
    virtual bool init();
    
    
    void update(float dt);    
    
    
    CREATE_FUNC(GameScene);
    
private:
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    void setWaterYPosition(float y);
    
    
    cocos2d::Size _visibleSize;
    
    cocos2d::Sprite *_waterContainer;
    cocos2d::Sprite *_waterBackground;
    cocos2d::Sprite *_waterForeground;
    
    Fisherman *_fisherman;
    
    BoatDirection _boatDirection;
    
};

#endif /* defined(__beneath_the_surface__GameScene__) */
