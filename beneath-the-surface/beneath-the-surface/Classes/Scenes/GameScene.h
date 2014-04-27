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
#include "Fish.h"
#include "Shark.h"
#include "Cloud.h"

class GameScene : public cocos2d::Layer
{
    
public:

    static cocos2d::Scene* createScene();
    virtual bool init();
    
    
    void update(float dt);    
    void play();
    void stop();
    bool getPlaying();
    
    CREATE_FUNC(GameScene);
    
private:
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    void setWaterYPosition(float y);
    void checkCollision();
    void updateScore();
    
    bool intersectRect(cocos2d::Rect r1, cocos2d::Rect r2);
    
    void removeCatch(bool alive, bool getScore);
    
    cocos2d::Size _visibleSize;
    
    cocos2d::Sprite *_waterContainer;
    cocos2d::Sprite *_waterForegorundContainer;
    cocos2d::Sprite *_waterBackground;
    cocos2d::Sprite *_waterForeground;
    
    Fish *_catchedFish;
    Shark *_shark;
    bool _forceSharkDirection;
    
    Fisherman *_fisherman;
    std::vector<Fish*> _fish;
    
    std::vector<Cloud*> _clouds;
    
    BoatDirection _boatDirection;
    
    bool _playing;
    float _fishAddTicker;
    float _turtleAddTicker;
    float _score;
    float _currentScore;
    float _scoreMultiplier;
    float _time;
    
    cocos2d::Label *_highscoreLabel;
    cocos2d::Label *_currentLabel;
    cocos2d::Label *_timeLabel;
    
    cocos2d::Layer *_menuLayer;
    
    int _seconds;

    
};

#endif /* defined(__beneath_the_surface__GameScene__) */
