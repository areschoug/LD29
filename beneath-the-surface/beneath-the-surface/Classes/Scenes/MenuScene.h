//
//  MenuScene.h
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 27/04/14.
//
//

#ifndef __beneath_the_surface__MenuScene__
#define __beneath_the_surface__MenuScene__

#include "cocos2d.h"
#include "GameScene.h"

class MenuScene : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void menuPlayCallback(cocos2d::Ref* pSender);
    
    void play();
    
    CREATE_FUNC(MenuScene);
    
    void setGameScene(GameScene *gameScene);
    void update(float dt);
    
    
    
private:
    GameScene *_gameScene;
    
    std::vector<Fish*> _fish;
};


#endif /* defined(__beneath_the_surface__MenuScene__) */
