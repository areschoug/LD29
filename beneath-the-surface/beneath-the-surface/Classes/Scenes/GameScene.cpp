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
    Point origin = Director::getInstance()->getVisibleOrigin();

    {//background
        auto background = LayerColor::create(kSkyBackgroundColor4B);
        this->addChild(background,kZBackground);
    }

    {//water
        _waterBackground = Sprite::create("blank.png", Rect(0, 0, _visibleSize.width, _visibleSize.height));
        _waterBackground->setColor(kWaterBackgroundColor3B);
        _waterBackground->setPosition(Point(_visibleSize.width/2, 0));
        this->addChild(_waterBackground, kZWaterBackground);

        _waterForeground = Sprite::create("blank.png", Rect(0, 0, _visibleSize.width, _visibleSize.height));
        _waterForeground->setColor(kWaterBackgroundColor3B);
        _waterForeground->setOpacity(128);
        _waterForeground->setPosition(Point(_visibleSize.width/2, 0));
        this->addChild(_waterForeground, kZWaterForeground);
    }
    
    
    setWaterYPosition(0);
    
    return true;
}


void GameScene::setWaterYPosition(float y){
    _waterBackground->setPosition(Point(_waterBackground->getPositionX(), MIN(_visibleSize.height/2, y)));
    _waterForeground->setPosition(_waterBackground->getPosition());
}

