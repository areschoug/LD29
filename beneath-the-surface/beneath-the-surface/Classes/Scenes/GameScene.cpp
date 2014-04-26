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
    
    {
        _shark = Shark::create();
        _shark->setPosition(Point(320, 100));
        this->addChild(_shark);
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

    {//shark
        
        
        if (_catchedFish) {
            _shark->update(dt);
            Point fish = _catchedFish->getPosition();
            Point shark = _shark->getPosition();
            float deltaY = shark.y - fish.y;
            float deltaX = shark.x - fish.x;

            float angleInRadians = atan2(deltaY, deltaX);
            float angleInDegrees = atan2(deltaY, deltaX) * 180 / M_PI;
            
            if (fish.x > shark.x) {
                _shark->setScaleX(-1);
                _shark->setRotation((angleInDegrees - 180) * -1);
            } else {
                _shark->setScaleX(1);
                _shark->setRotation(angleInDegrees * -1);
            }

            float velocity = -3;
            _shark->setPosition(Point(shark.x + (cos(angleInRadians) * velocity),
                                      shark.y + (sin(angleInRadians) * velocity)));
            

            if (intersectRect(_shark->getBoundingBox(), _catchedFish->getBoundingBox())) {
                log("eat bitch + %i ", rand());
                removeCatch(false, false);
            }
            
            
        } else {
            
            Point position = _shark->getPosition();

            if (position.x < -50 || position.x > _visibleSize.width + 50 || _forceSharkDirection) {
                _forceSharkDirection = false;
                float xSpeed = 85;
                
                if (position.y > 250) {
                    _shark->setVelocity(Point(position.x < _visibleSize.width/2 ? xSpeed : -xSpeed ,
                                              -20));
                } else {
                    _shark->setVelocity(Point(position.x < _visibleSize.width/2 ? xSpeed : -xSpeed,
                                              (rand()%2) ? -4 : 4));
                    
                }
                
                if (_shark->getVelocity().x < 0) {
                    _shark->setScaleX(1);
                } else {
                    _shark->setScaleX(-1);
                }
                
                
            }
            
            Point vel = _shark->getVelocity();
            _shark->setPosition(position.x + (vel.x * dt), position.y + (vel.y * dt));
            
            
        }
    
    }
    
    
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
                
                removeCatch(false, true);
            }
        } else {
            if(_catchedFish){
                removeCatch(true, false);
                _catchedFish->setRotation(0);
                

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

void GameScene::removeCatch(bool alive, bool getScore){
    
    if (!alive) {
        _fish.erase(std::remove(_fish.begin(), _fish.end(), _catchedFish), _fish.end());
        _catchedFish->removeFromParent();
    }
    
    if (getScore) {
        //TODO: give score here
    }
    
    _catchedFish = NULL;
    _forceSharkDirection = true;
    _shark->resetAnimation();
    

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


bool GameScene::intersectRect(Rect r1, Rect r2) {
    
    return !(r2.getMinX() > r1.getMaxX() ||
             r2.getMaxX() < r1.getMinX() ||
             r2.getMinY() > r1.getMaxY() ||
             r2.getMaxY() < r1.getMinY());
}

