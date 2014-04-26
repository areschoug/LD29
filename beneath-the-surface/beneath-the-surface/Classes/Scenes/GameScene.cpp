//
//  GameScene.cpp
//  beneath-the-surface
//
//  Created by Andreas Areschoug on 26/04/14.
//
//

#include "GameScene.h"
#include "Defines.h"
#include "StandardFish.h"
#include "Turtle.h"

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
        
        _waterForegorundContainer = Sprite::create();
        _waterForegorundContainer->setAnchorPoint(Point(0,0));

        
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
        _waterForeground->setOpacity(150);
        _waterForeground->setAnchorPoint(Point(0, 0));
        _waterForeground->setPosition(Point(0, 0));
        _waterForegorundContainer->addChild(_waterForeground, kZWaterForeground);

        this->addChild(_waterContainer);
        this->addChild(_waterForegorundContainer,kZWaterForeground);
    }
    
    
    {
        this->setKeyboardEnabled(true);
        scheduleUpdate();
    }
    
    
    
    setWaterYPosition(-200);
    
    return true;
}


void GameScene::setWaterYPosition(float y){
    _waterContainer->setPosition(Point(0, MIN(_fisherman->getContentSize().height, y)));
    _waterForegorundContainer->setPosition(_waterContainer->getPosition());
}

#pragma mark - help
void GameScene::checkCollision(){
    std::vector<int> catched;
    
    for (int i = 0; i < _fish.size(); i++) {
        Fish *fish = _fish.at(i);
        Point fishPoint = fish->getPosition();
        Size fishSize = Size(fish->getContentSize().width * fabs(fish->getScaleX()), fish->getContentSize().height * fabs(fish->getScaleY()));
        Point hookpoint = _fisherman->getHookWorldPoint();
        
        bool x = false;
        bool y = false;
        
        if (((fishPoint.x - (fishSize.width/2)) < hookpoint.x) &&
            ((fishPoint.x + (fishSize.width/2)) > hookpoint.x)) {
            x = true;
        }
        
        if (((fishPoint.y - (fishSize.height/2)) < hookpoint.y) &&
            ((fishPoint.y + (fishSize.height/2)) > hookpoint.y)) {
            y = true;
        }
        
        if (x && y) {
            catched.push_back(i);
        }
    }
    
    for (int i = 0; i < catched.size(); i++) {
        int x = catched.at(i);
        Fish *f = _fish.at(x);
        if (!_catchedFish) {
            _catchedFish = f;
            _catchedFish->setRotation(_catchedFish->getScaleX() > 0 ? 90 : 270);
        } else if(f->getScore() > _catchedFish->getScore()) {
            f->setScore(f->getScore() + _catchedFish->getScore());
            _fish.erase(std::remove(_fish.begin(), _fish.end(), _catchedFish), _fish.end());
            _catchedFish->removeFromParent();
            _catchedFish = NULL;
            
            _catchedFish = f;
            _catchedFish->setRotation(_catchedFish->getScaleX() > 0 ? 90 : 270);
        }
        
    }
}

#pragma mark - game loop
void GameScene::update(float dt){

    _fisherman->update(dt);
    
    for (int i = 0; i < _fish.size(); i++) {
        Fish *f = _fish.at(i);
        
        f->update(dt);
    }
    
    if (_fisherman->getThrowState() == ThrowStateThrowing) {
        checkCollision();
        if (_catchedFish) {
            _catchedFish->setPosition(_fisherman->getHookWorldPoint());
        }
    } else {
        if (_fisherman->getBoatDirection() == BoatDirectionNone){
            if (_catchedFish) {
                //TODO: save points here
                _fish.erase(std::remove(_fish.begin(), _fish.end(), _catchedFish), _fish.end());
                _catchedFish->removeFromParent();
                _catchedFish = NULL;
            }
        } else {
            if(_catchedFish){
                _catchedFish->setRotation(0);
                _catchedFish = NULL;
            }
        }
    }
        
    //fish
    _turtleAddTicker += dt;
    if (_turtleAddTicker > 8) {
        _turtleAddTicker -= 8;
        
        Turtle *fish = Turtle::create();
        this->addChild(fish);
        
        _fish.push_back(fish);
    }
    _fishAddTicker += dt;
    if (_fishAddTicker > 2) {
        _fishAddTicker -= 2;
        
        StandardFish *f = StandardFish::create();
        this->addChild(f);
        
        _fish.push_back(f);
    }
    
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

