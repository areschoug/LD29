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
#include "SimpleAudioEngine.h"
#include "MenuScene.h"


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
        this->touchScreens();
    }
    
    {
        _shark = Shark::create();
        _shark->setPosition(Point(320, 100));
        this->addChild(_shark);
    }
    
    {//high score label

        _highscoreLabel = Label::createWithTTF("000000", "STAN0764.TTF", 18);
        _highscoreLabel->setAlignment(TextHAlignment::LEFT);
        _highscoreLabel->setString("");
        
        _highscoreLabel->setPosition(Point(10, _visibleSize.height - 20));
        _highscoreLabel->setAnchorPoint(Point(0,0.5));
        this->addChild(_highscoreLabel, 1);
        
        _currentLabel = Label::createWithTTF("000000", "STAN0764.TTF", 14);
        _currentLabel->setAlignment(TextHAlignment::LEFT);
        _currentLabel->setPosition(Point(10, _visibleSize.height - 40));
        _currentLabel->setAnchorPoint(Point(0,0.5));
        _currentLabel->setColor(Color3B(255,225,117));
        this->addChild(_currentLabel, 1);
        _currentLabel->setString("");
        
        
        _timeLabel = Label::createWithTTF("", "STAN0764.TTF", 18);
        _timeLabel->setAlignment(TextHAlignment::LEFT);
        _timeLabel->setPosition(Point(_visibleSize.width - 5, _visibleSize.height - 20));
        _timeLabel->setAnchorPoint(Point(1, 0.5));
        this->addChild(_timeLabel, 1);
        _timeLabel->setString("");
        
    }
    
    
    
    {
        Sprite *ground = Sprite::create("blank.png");
        
        ground->setPosition(Point(_visibleSize.width/2.0, 4));
        ground->setColor(Color3B(84,69,8));
        ground->setScaleX(_visibleSize.width/4);
        ground->setScaleY(4);
        
        this->addChild(ground);
    }
    
    {
    
        Cloud *c1 = Cloud::create("cloud_1.png");
        c1->setPosition(-400, _visibleSize.height - 80);
        c1->setVelocity(Point(26, 0));
        this->addChild(c1);
        _clouds.push_back(c1);
        
        Cloud *c2 = Cloud::create("cloud_2.png");
        c2->setPosition(-10, _visibleSize.height - 50);
        c2->setVelocity(Point(20, 0));
        this->addChild(c2);
        _clouds.push_back(c2);
        
        Cloud *c3 = Cloud::create("cloud_3.png");
        c3->setPosition(_visibleSize.width + 300, _visibleSize.height - 40);
        c3->setVelocity(Point(-20, 0));
        this->addChild(c3);
        _clouds.push_back(c3);
        
        Cloud *c4 = Cloud::create("cloud_4.png");
        c4->setPosition(_visibleSize.width + 40, _visibleSize.height - 70);
        c4->setVelocity(Point(-15, 0));
        this->addChild(c4);
        _clouds.push_back(c4);
        
        
    }
    
    {
        MenuScene *menu = MenuScene::create();
        menu->setGameScene(this);
        this->addChild(menu,9999999);
        _menuLayer = menu;
    }
    
    setWaterYPosition(-200);
    
    return true;
}

bool GameScene::getPlaying(){
    return _playing;
}

void GameScene::play(){
    _playing = true;
    _currentScore = 0;
    _score = 0;
    _scoreMultiplier = 0;
    _time = 50;
    updateScore();
    _menuLayer->runAction(Sequence::createWithTwoActions(DelayTime::create(0), MoveTo::create(0.3, Point(-_visibleSize.width, 0))));
}

void GameScene::stop(){
    _fisherman->setBoatDirection(BoatDirectionLeft);
    _fisherman->setBoatDirection(BoatDirectionNone);
    _playing = false;
    _menuLayer->runAction(Sequence::createWithTwoActions(DelayTime::create(0), MoveTo::create(0.3, Point(0, 0))));
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
        if (!fish->getIsCatched()) {
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
    }
    
    for (int i = 0; i < catched.size(); i++) {
        int x = catched.at(i);
        Fish *f = _fish.at(x);
        if(f != _catchedFish) {
            f->setIsCatched(true);
            if (!_catchedFish) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("new_pick_up.wav");
                _catchedFish = f;
                _catchedFish->setPreventAnimations(true);
                _catchedFish->setRotation(_catchedFish->getScaleX() > 0 ? 90 : 270);
                _scoreMultiplier = 1;
                
                _currentScore = _catchedFish->getScore();
                
            } else {
                if (!dynamic_cast<Turtle*>(f)) {
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("new_pick_up.wav");
                    _scoreMultiplier ++;
                    
                    if (f->getScore() > _catchedFish->getScore()) {
                        //                f->setScore(f->getScore());
                        _fish.erase(std::remove(_fish.begin(), _fish.end(), _catchedFish), _fish.end());
                        _catchedFish->removeFromParent();
                        _catchedFish = NULL;
                        
                        
                        _catchedFish = f;
                        _currentScore += _catchedFish->getScore();
                        _catchedFish->setPreventAnimations(true);
                        _catchedFish->setRotation(_catchedFish->getScaleX() > 0 ? 90 : 270);
                        
                    } else {
                        _currentScore += f->getScore();
                        _fish.erase(std::remove(_fish.begin(), _fish.end(), f), _fish.end());
                        f->removeFromParent();
                        f = NULL;
                        
                    }

                }
                
                
            }

        }
        
        
    }
    
    if (_currentScore > 0) {
        char buff[100];
        sprintf(buff, "%dX%i", (int)roundf(_currentScore),(int)_scoreMultiplier);
        std::string buffAsStdStr = buff;
        _currentLabel->setString(buffAsStdStr);
        
    }
    
}

#pragma mark - game loop
void GameScene::update(float dt){

    _fisherman->update(dt);

    {//time
        if (_playing) {
            _time -= dt;
            int preSec = _seconds;
            _seconds = (int)roundf(MAX(0, _time));
            
            if (_seconds <= 5 && _seconds != preSec) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("count_down.wav");
            }
            
            char buff[100];
            sprintf(buff, "%02d", _seconds);
            std::string buffAsStdStr = buff;
            
            _timeLabel->setString(buffAsStdStr);
            
            if (_time < 0) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("count_down_done.wav");
                stop();
            }
        }
    
    }
    
    {//cloud
        for (int i = 0; i < _clouds.size(); i++) {
            Cloud *c = _clouds.at(i);
            c->update(dt);
        }
    }

    {//shark
        _shark->hurtUpdate(dt);

        
        if (_catchedFish && !_shark->getHurt()) {
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
                if (dynamic_cast<Turtle*>(_catchedFish)) {
                    _shark->setHurt();
                }
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
                } else if(position.y < 20){
                    _shark->setVelocity(Point(position.x < _visibleSize.width/2 ? xSpeed : -xSpeed,
                                              10));
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

void GameScene::updateScore(){
    
    char buff[100];
    sprintf(buff, "%05d", (int)roundf(_score));
    std::string buffAsStdStr = buff;
    
    _highscoreLabel->setString(buffAsStdStr);
}

void GameScene::removeCatch(bool alive, bool getScore){

    if (getScore) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("add_point.wav");
        _score += (_currentScore * _scoreMultiplier);
        updateScore();
    }
    _currentScore = 0;
    _scoreMultiplier = 0;
    
    _currentLabel->setString("");
    
    if (alive) {
        _catchedFish->setPreventAnimations(false);
        _catchedFish->setRotation(0);
        _catchedFish->setIsCatched(false);
    } else {
        _fish.erase(std::remove(_fish.begin(), _fish.end(), _catchedFish), _fish.end());
        _catchedFish->removeFromParent();
    
        if (!getScore) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("eaten.wav");
        }
        
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
            if (_playing) {
                _fisherman->doPower();
            }
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
            if (_playing) {
                _fisherman->doThrow();
            }
            break;
        default:
            break;
    }
    
}

void GameScene::touchScreens(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = listener->onTouchEnded;
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
#endif
}


bool GameScene::intersectRect(Rect r1, Rect r2) {
    
    return !(r2.getMinX() > r1.getMaxX() ||
             r2.getMaxX() < r1.getMinX() ||
             r2.getMinY() > r1.getMaxY() ||
             r2.getMaxY() < r1.getMinY());
}

bool GameScene::onTouchBegan( Touch *pTouches, Event *pEvent ){
    
    Point touch = pTouches->getLocation();
    
    if (touch.x < (_visibleSize.width/10)) {
        _touchLocation = TouchLeft;
        _fisherman->setBoatDirection(BoatDirectionLeft);
    } else if(touch.x > ((_visibleSize.width/10) * 9)){
        _touchLocation = TouchRight;
        _fisherman->setBoatDirection(BoatDirectionRight);
    } else {
        _touchLocation = TouchMiddle;
        if (_playing) {
            _fisherman->doPower();
        }
    }
    
    
    return true;

}

void GameScene::onTouchMoved( Touch *pTouches, Event *pEvent )
{

}

void GameScene::onTouchEnded( Touch *pTouches, Event *pEvent )
{
    
    
    if (_touchLocation == TouchLeft) {
        if (_fisherman->getBoatDirection() == BoatDirectionLeft) {
            _fisherman->setBoatDirection(BoatDirectionNone);
        }
    } else if(_touchLocation == TouchRight){
        if (_fisherman->getBoatDirection() == BoatDirectionRight) {
            _fisherman->setBoatDirection(BoatDirectionNone);
        }
    } else {
        if (_playing) {
            _fisherman->doThrow();
        }
    }



}

