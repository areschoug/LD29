//
//  MenuScene.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 27/04/14.
//
//

#include "MenuScene.h"
#include "StandardFish.h"
#include "Shark.h"
#include "Turtle.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();



    {//name
        auto label = Label::createWithTTF("FISH!", "STAN0764.TTF", 50);
        
        label->setPosition(Point(visibleSize.width/2, visibleSize.height - 60));
        label->setColor(Color3B(250,223,117));
        this->addChild(label, 1);
        {
            auto label = Label::createWithTTF("FISH!", "STAN0764.TTF", 50);
            
            label->setPosition(Point(visibleSize.width/2, visibleSize.height - 63));
            label->setColor(Color3B(255,255,255));
            this->addChild(label, 0);
        }
        
    
    }
    
    {//control
        auto label = Label::createWithTTF("CONTROLS", "STAN0764.TTF", 22);
        
        label->setPosition(Point(visibleSize.width/2, visibleSize.height - 240));
        label->setColor(Color3B(250,223,117));
        this->addChild(label, 1);

    }
    
    {//control
        auto label = Label::createWithTTF("left, right and space", "STAN0764.TTF", 14);
        
        label->setPosition(Point(visibleSize.width/2, visibleSize.height - 270));
        label->setColor(Color3B(250,223,117));
        this->addChild(label, 1);
        
    }
    
    {//game play
        auto label = Label::createWithTTF("GAME PLAY", "STAN0764.TTF", 22);
        
        label->setPosition(Point(visibleSize.width/2, 300));
        label->setColor(Color3B(250,223,117));
        this->addChild(label, 1);
        
    }
    
    {//Game play
    
        StandardFish *fish = StandardFish::create();
        fish->setPosition(Point(90, 250));
        fish->setRotation(0);
        fish->setScale(-1, 1);
        this->addChild(fish);
        
        _fish.push_back(fish);
        
    }
    
    {//control
        auto label = Label::createWithTTF("<", "STAN0764.TTF", 28);
        
        label->setPosition(Point(132, 250));
        label->setColor(Color3B(250,223,117));
        this->addChild(label, 1);
        
    }
    
    {//Game play
        
        StandardFish *fish = StandardFish::create();
        fish->setPosition(Point(155, 250));
        fish->setRotation(90);
        fish->setScale(1, 1);
        this->addChild(fish);


    }
    
    
    {//Game play
        
        StandardFish *fish = StandardFish::create();
        fish->setPosition(Point(210, 250));
        fish->setRotation(0);
        fish->setScale(-1, 1);
        this->addChild(fish);
        
        _fish.push_back(fish);
    }
    
    {//control
        auto label = Label::createWithTTF("<", "STAN0764.TTF", 28);
        
        label->setPosition(Point(252, 250));
        label->setColor(Color3B(250,223,117));
        this->addChild(label, 1);
        
    }
    
    {//Game play
        
        Turtle *fish = Turtle::create();
        fish->setPosition(Point(275, 250));
        fish->setRotation(90);
        fish->setScale(1, 1);
        this->addChild(fish);
        
    }
    
    {//Game play
        
        Shark *fish = Shark::create();
        fish->setPosition(Point(345, 250));
        fish->setRotation(0);
        fish->setScale(-1, 1);
        this->addChild(fish);
        _fish.push_back(fish);
        
    }
    
    {//control
        auto label = Label::createWithTTF("<", "STAN0764.TTF", 28);
        
        label->setPosition(Point(400, 250));
        label->setColor(Color3B(250,223,117));
        this->addChild(label, 1);
        
    }
    
    {//Game play
        
        StandardFish *fish = StandardFish::create();
        fish->setPosition(Point(425, 250));
        fish->setRotation(90);
        fish->setScale(1, 1);
        this->addChild(fish);
        
    }
    
    {//Game play
        
        Shark *fish = Shark::create();
        fish->setPosition(Point(490, 250));
        fish->setRotation(0);
        fish->setScale(-1, 1);
        this->addChild(fish);
        _fish.push_back(fish);
        fish->setHurt();
        fish->setQuiet(true);
    }
    
    {//control
        auto label = Label::createWithTTF("<", "STAN0764.TTF", 28);
        
        label->setPosition(Point(545, 250));
        label->setColor(Color3B(250,223,117));
        this->addChild(label, 1);
        
    }
    
    {//Game play
        
        Turtle *fish = Turtle::create();
        fish->setPosition(Point(580, 250));
        fish->setRotation(90);
        fish->setScale(1, 1);
        this->addChild(fish);
        
    }
    
    
    {//credit
        auto label = Label::createWithTTF("ludum dare 29\n@yo_pox", "STAN0764.TTF", 14);
        
        label->setPosition(Point(76, 160));
        label->setColor(Color3B(250,223,117));
        label->setAnchorPoint(Point(0, 0.5));
        
        this->addChild(label, 1);
    }
    

    
    
    
    
    auto playItem = MenuItemImage::create(
                                           "play_button.png",
                                           "play_button_pressed.png",
                                           CC_CALLBACK_1(MenuScene::menuPlayCallback, this));
    
    
	playItem->setPosition(Point(visibleSize.width/2 ,
                                 (playItem->getContentSize().height/2) + 20));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    
    {
        this->setKeyboardEnabled(true);
        scheduleUpdate();
    }
    
    for (int i = 0; i < _fish.size(); i++) {
        Fish *f = _fish.at(i);
        f->setVelocity(Point(0, 0));
    }
    
    
    return true;
}


void MenuScene::update(float dt){
    for (int i = 0; i < _fish.size(); i++) {
        Fish *f = _fish.at(i);
        f->update(dt);
        
        if (dynamic_cast<Shark *>(f)) {
            Shark *s = (Shark *)f;
            if (s->getHurt()) {
                s->setHurt();
                s->hurtUpdate(dt);
            }
        }
    }
}

void MenuScene::menuPlayCallback(Ref* pSender) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("new_pick_up.wav");    
    play();
}

void MenuScene::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event){
    
    switch (keyCode) {

        case EventKeyboard::KeyCode::KEY_SPACE:
            //play();
            break;
            
        default:
            break;
    }
    
    
}

void MenuScene::play(){
    if(!_gameScene->getPlaying()){
        _gameScene->play();
    }
}

void MenuScene::setGameScene(GameScene *gameScene){
    _gameScene = gameScene;
}
