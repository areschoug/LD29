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

class GameScene : public cocos2d::Layer
{
    
public:

    static cocos2d::Scene* createScene();
    virtual bool init();
    
    
    
    
    
    CREATE_FUNC(GameScene);
    
private:
    
    void setWaterYPosition(float y);
    
    cocos2d::Size _visibleSize;
    
    cocos2d::Sprite *_waterBackground;
    cocos2d::Sprite *_waterForeground;
};

#endif /* defined(__beneath_the_surface__GameScene__) */
