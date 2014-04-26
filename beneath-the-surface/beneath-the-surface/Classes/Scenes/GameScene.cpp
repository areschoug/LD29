//
//  GameScene.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#include "GameScene.h"
#include "Defines.h"



USING_NS_CC;

Scene* GameScene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool GameScene::init() {
    if (!Layer::init()){
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    //Point origin = Director::getInstance()->getVisibleOrigin();

    {//background
        auto background = LayerColor::create(kSkyBackgroundColor4B);
        this->addChild(background,kZBackground);
    }
    
    {//water container
        _waterContainer = Sprite::create();
        _waterContainer->setAnchorPoint(Point(0,0));
    
    }
    
    
    {//fisherman

        _fisherman = Fisherman::create();
        _fisherman->setAnchorPoint(Point(0.5, 0.25));//set the anchor point in the boat
        _fisherman->setPosition(_visibleSize.width/2.0, _visibleSize.height + _fisherman->getContentSize().height);
        _waterContainer->addChild(_fisherman);
        
    }

    {//water
        
        Rect rect = Rect(0, 0, _visibleSize.width, _visibleSize.height +_fisherman->getContentSize().height);
        
        _waterBackground = Sprite::create("blank.png", rect);
        _waterBackground->setColor(kWaterBackgroundColor3B);
        _waterBackground->setAnchorPoint(Point(0, 0));
        _waterBackground->setPosition(Point(0, 0));
        _waterContainer->addChild(_waterBackground, kZWaterBackground);

        _waterForeground = Sprite::create("blank.png", rect);
        _waterForeground->setColor(kWaterBackgroundColor3B);
        _waterForeground->setOpacity(200);
        _waterForeground->setAnchorPoint(Point(0, 0));
        _waterForeground->setPosition(Point(0, 0));
        _waterContainer->addChild(_waterForeground, kZWaterForeground);

        this->addChild(_waterContainer);
    }
    

    
    {
        this->setKeyboardEnabled(true);
        scheduleUpdate();
    }
    
    
    
    setWaterYPosition(-400);
    
    return true;
}


void GameScene::setWaterYPosition(float y){
    _waterContainer->setPosition(Point(0, MIN(_fisherman->getContentSize().height, y)));
}


#pragma mark - game loop
void GameScene::update(float dt){

    _fisherman->update(dt);

    
}

#pragma mark - keyboard
void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
    
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _fisherman->setBoatDirection(BoatDirectionLeft);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _fisherman->setBoatDirection(BoatDirectionRight);
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            _fisherman->doPower();
            break;
            
        default:
            break;
    }

    
}



void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event){

    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            if (_fisherman->getBoatDirection() == BoatDirectionLeft) {
                _fisherman->setBoatDirection(BoatDirectionNone);
            }
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            if (_fisherman->getBoatDirection() == BoatDirectionRight) {
                _fisherman->setBoatDirection(BoatDirectionNone);
            }
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            _fisherman->doThrow();
            break;
        default:
            break;
    }
    
}

