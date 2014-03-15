#include "HelloWorldScene.h"
#include "KRActor.h"
#include "MSDataStructure.h"
#include "TypeConver.h"
#include "AnimationConfig.h"
#include "KRActor.h"
#include "KRScene.h"
#include "MSGeometry.h"
#include "KRFireCircleConfig.h"

USING_NS_CC;

void MainScene::onUpCallBack(cocos2d::Object *obj)
{
    bool hasAdd = fireCircleScene->upSpeed();
    if (hasAdd)
    {
        roadScene->upSpeed();
        shanRollScene->upSpeed();
        layer1RollScene->upSpeed();
        layer2RollScene->upSpeed();
        layer3RollScene->upSpeed();
        
        std::string sstr = "当前速度";
        sstr += moonsugar::TypeConver::intToString(fireCircleScene->currentSpeed);
        uiLayer->speedLabel->setString(sstr);
    }
}

void MainScene::onDownCallBack(cocos2d::Object *obj)
{
    bool hasAdd = fireCircleScene->downSpeed();
    if (hasAdd)
    {
        roadScene->downSpeed();
        shanRollScene->downSpeed();
        layer1RollScene->downSpeed();
        layer2RollScene->downSpeed();
        layer3RollScene->downSpeed();
        
        std::string sstr = "当前速度";
        sstr += moonsugar::TypeConver::intToString(fireCircleScene->currentSpeed);
        uiLayer->speedLabel->setString(sstr);
    }
}

void MainScene::onEnter()
{
    Scene::onEnter();
    
    actor->pauseAction();
}

void MainScene::onHitHandler()
{
    //hit
    roadScene->pause();
    shanRollScene->pause();
    layer1RollScene->pause();
    layer2RollScene->pause();
    layer3RollScene->pause();
    fireCircleScene->pause();
    actor->pauseAction();
    
    uiLayer->changeMenuState(GAME_STATE_DEAD);
}

void MainScene::onCloseCallBack(cocos2d::Object *pSender)
{
    keepRun::BehaviorJumpEvent *jump = new keepRun::BehaviorJumpEvent(JUMP_EVENT);
    actor->executeEvent(jump);
    jump = nullptr;
}

void MainScene::onPauseCallBack(cocos2d::Object *obj)
{
    //cocos2d::log("%s", "pause click");
    roadScene->pause();
    shanRollScene->pause();
    layer1RollScene->pause();
    layer2RollScene->pause();
    layer3RollScene->pause();
    fireCircleScene->pause();
    actor->pauseAction();
    
    uiLayer->changeMenuState(GAME_STATE_WAITING_START);
}

void MainScene::onContinueCallBack(cocos2d::Object *obj)
{
    //cocos2d::log("%s", "continue click");
    roadScene->start();
    shanRollScene->start();
    layer1RollScene->start();
    layer2RollScene->start();
    layer3RollScene->start();
    fireCircleScene->start();
    actor->continueAction();
    
    uiLayer->changeMenuState(GAME_STATE_RUNNING);
}

void MainScene::onRestartCallBack(cocos2d::Object *obj)
{
    //cocos2d::log("%s", "restart click");
    roadScene->start();
    shanRollScene->start();
    layer1RollScene->start();
    layer2RollScene->start();
    layer3RollScene->start();
    fireCircleScene->restart();
    actor->continueAction();
    
    uiLayer->changeMenuState(GAME_STATE_RUNNING);
}

MainScene * MainScene::create()
{
    MainScene *ret = new MainScene();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void MainScene::update(float dt)
{
    Scene::update(dt);
    
    if (roadScene && roadScene->isRolling)
    {
        roadScene->update(dt);
    }
    if (shanRollScene && shanRollScene->isRolling)
    {
        shanRollScene->update(dt);
    }
    if (layer1RollScene && layer1RollScene->isRolling)
    {
        layer1RollScene->update(dt);
    }
    if (layer2RollScene && layer2RollScene->isRolling)
    {
        layer2RollScene->update(dt);
    }
    if (layer3RollScene && layer3RollScene->isRolling)
    {
        layer3RollScene->update(dt);
    }
    if (fireCircleScene && fireCircleScene->isRolling)
    {
        fireCircleScene->update(dt);
    }
    
    if (actor && actor->isJumping)
    {
        actor->update(dt);
    }
}

bool MainScene::init()
{
    // 1. super init first
    if ( !Scene::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    /***to do 这个rect可能引起内存泄露***/
    cocos2d::Rect rect(origin.x, origin.y, visibleSize.width, visibleSize.height);
    
    
    auto shanLayer = cocos2d::Layer::create();
    auto layer1 = cocos2d::Layer::create();
    auto layer2 = cocos2d::Layer::create();
    auto layer3 = cocos2d::Layer::create();
    auto circleRoadLeft = cocos2d::Layer::create();
    auto roadLayer = cocos2d::Layer::create();
    auto circleRoadright = cocos2d::Layer::create();
    
    std::string roadFullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename("scene.plist");
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(roadFullPath);
    
    cocos2d::SpriteFrame * shanSpriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("shan001.png");
    shanRollScene = new keepRun::RollScene(shanLayer, SCENE_INIT_SPEED - SCENE_ADD_SPEED * 3, shanSpriteFrame, rect, ANIMATION_CONFIG_DELAY);
    shanRollScene->tile();
    this->addChild(shanLayer);
    shanLayer->setPositionY(350);
    cocos2d::SpriteFrame * layer1SpriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("shu001.png");
    layer1RollScene = new keepRun::RollScene(layer1, SCENE_INIT_SPEED - SCENE_ADD_SPEED * 2, layer1SpriteFrame, rect, ANIMATION_CONFIG_DELAY);
    layer1RollScene->tile();
    this->addChild(layer1);
    layer1->setPositionY(300);
    cocos2d::SpriteFrame * layer2SpriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("shu004.png");
    layer2RollScene = new keepRun::RollScene(layer2, SCENE_INIT_SPEED - SCENE_ADD_SPEED, layer2SpriteFrame, rect, ANIMATION_CONFIG_DELAY);
    layer2RollScene->tile();
    this->addChild(layer2);
    layer2->setPositionY(260);
    cocos2d::SpriteFrame * layer3SpriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("shu003.png");
    layer3RollScene = new keepRun::RollScene(layer3, SCENE_INIT_SPEED, layer3SpriteFrame, rect, ANIMATION_CONFIG_DELAY);
    layer3RollScene->tile();
    this->addChild(layer3);
    layer3->setPositionY(210);
    
    cocos2d::SpriteFrame * roadSpriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("road001.png");
    roadScene = new keepRun::RollScene(roadLayer, SCENE_INIT_SPEED, roadSpriteFrame, rect, ANIMATION_CONFIG_DELAY);
    roadScene->tile();
    this->addChild(roadLayer);
    roadLayer->setPositionY(SCENE_ROAD_Y);
    
    //fireCircle
    std::string fireconfig = cocos2d::FileUtils::getInstance()->fullPathForFilename("fireCircleConfig.plist");
    ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(fireconfig);
    keepRun::FireCircleConfig * fireConfig = new keepRun::FireCircleConfig(dict);
    
    this->addChild(circleRoadLeft);

    std::string fireSourceFullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename("fireCircle.plist");
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fireSourceFullPath);
    cocos2d::SpriteFrame * rectSpriteFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("rect.png");
    auto fireCircleLayer = cocos2d::Layer::create();
    this->addChild(fireCircleLayer);
    
    auto actorLayer = Layer::create();
    this->addChild(actorLayer);
    
    this->addChild(circleRoadright);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    // add layer as a child to scene
    uiLayer = layer;
    this->addChild(layer);
    layer->callBackPointer = this;
    layer->closeCallBack = cocos2d::SEL_CallFuncO(&MainScene::onCloseCallBack);
    layer->pauseCallBack = cocos2d::SEL_CallFuncO(&MainScene::onPauseCallBack);
    layer->continueCallBack = cocos2d::SEL_CallFuncO(&MainScene::onContinueCallBack);
    layer->restartCallBack = cocos2d::SEL_CallFuncO(&MainScene::onRestartCallBack);
    layer->upCallBack = cocos2d::SEL_CallFuncO(&MainScene::onUpCallBack);
    layer->downCallBack = cocos2d::SEL_CallFuncO(&MainScene::onDownCallBack);
    layer->changeMenuState(GAME_STATE_WAITING_START);
    //chick
    std::string plistFullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename("chickAnimation.plist");
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistFullPath);
    cocos2d::Map<std::string, cocos2d::Animation *> map0;
    cocos2d::Vector<cocos2d::SpriteFrame *> runList = keepRun::AnimationConfig::getRunForArray(cocos2d::SpriteFrameCache::getInstance());
    cocos2d::Animation * runAnimation = keepRun::AnimationConfig::createAnimation(runList, ANIMATION_CONFIG_DELAY);
    map0.insert(ANIMATION_CONFIG_RUN01, runAnimation);
    cocos2d::Vector<cocos2d::SpriteFrame *> jumpList = keepRun::AnimationConfig::getJumpForArray(cocos2d::SpriteFrameCache::getInstance());
    cocos2d::Animation * jumpAnimation = keepRun::AnimationConfig::createAnimation(jumpList, ANIMATION_CONFIG_DELAY);
    map0.insert(ANIMATION_CONFIG_JUMP01, jumpAnimation);
    cocos2d::Sprite * body = cocos2d::Sprite::create();
    cocos2d::Sprite * bodyRect = cocos2d::Sprite::createWithSpriteFrame(rectSpriteFrame);
    actor = new keepRun::Actor();
    keepRun::ActorEntry * entry = new keepRun::ActorEntry(map0, body, bodyRect);
    actor->entry = entry;
    cocos2d::Point * point = new cocos2d::Point(INIT_X, INIT_Y);
    actor->setPosition(*point);
    actorLayer->addChild(bodyRect);
    actorLayer->addChild(body);
    keepRun::BehaviorRunEvent *behaviorRunEvent = new keepRun::BehaviorRunEvent(RUN_EVENT);
    actor->executeEvent(behaviorRunEvent);
    
    cocos2d::Vector<cocos2d::SpriteFrame *> leftCircles = keepRun::AnimationConfig::getLeftFireCircleForArray(cocos2d::SpriteFrameCache::getInstance());
    cocos2d::Vector<cocos2d::SpriteFrame *> rightCircles = keepRun::AnimationConfig::getRightFireCircleForArray(cocos2d::SpriteFrameCache::getInstance());
    fireCircleScene = new keepRun::FireCircleScene(fireConfig, fireCircleLayer, rectSpriteFrame, rect, ANIMATION_CONFIG_DELAY, circleRoadLeft, circleRoadright, leftCircles, rightCircles);
    fireCircleScene->actor = actor;
    fireCircleScene->callBackPointer = this;
    fireCircleScene->onHitHandler = cocos2d::SEL_CallFunc(&MainScene::onHitHandler);
    
    fireCircleScene->distance = uiLayer->distance;
    
    roadScene->pause();
    shanRollScene->pause();
    layer1RollScene->pause();
    layer2RollScene->pause();
    layer3RollScene->pause();
    fireCircleScene->pause();
    
    this->scheduleUpdate();
    
    return true;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    //cocos2d::log("width %f, height %f", visibleSize.width, visibleSize.height);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    jumpButton = MenuItemImage::create(
                                           "close.png",
                                           "close.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	jumpButton->setPosition(Point(origin.x + visibleSize.width - jumpButton->getContentSize().width/2 ,
                                origin.y + jumpButton->getContentSize().height/2));
    
    continueButton = cocos2d::MenuItemImage::create("continue.png", "continue.png", CC_CALLBACK_1(HelloWorld::onContinueHandler, this));
    continueButton->setPosition(Point(origin.x + visibleSize.width - continueButton->getContentSize().width * .5
                                      , origin.y - continueButton->getContentSize().height * .5 + visibleSize.height
                                      ));
    pauseButton = cocos2d::MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_1(HelloWorld::onPauseHandler, this));
    pauseButton->setPosition(continueButton->getPosition());
    restartButton = cocos2d::MenuItemImage::create("restart.png", "restart.png", CC_CALLBACK_1(HelloWorld::onRestartHandler, this));
    restartButton->setPosition(Point(origin.x + visibleSize.width * .5, origin.y + visibleSize.height * .5));
    
    upButton = cocos2d::MenuItemImage::create("up.png", "up.png", CC_CALLBACK_1(HelloWorld::onUpHandler, this));
    downbutton = cocos2d::MenuItemImage::create("down.png", "down.png", CC_CALLBACK_1(HelloWorld::onDownHandler, this));
    downbutton->setPosition(Point(origin.x + downbutton->getContentSize().width * .5 + 200, origin.y + downbutton->getContentSize().height * .5));
    upButton->setPosition(Point(origin.x + downbutton->getContentSize().width + upButton->getContentSize().width * .5 + 200, downbutton->getPositionY()));
    // create menu, it's an autorelease object
    auto menu = Menu::create(jumpButton, continueButton, pauseButton, restartButton, upButton, downbutton, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Demo", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    std::string speedStr = "当前速度";
    speedStr += moonsugar::TypeConver::intToString(SCENE_INIT_SPEED);
    speedLabel = LabelTTF::create(speedStr.c_str(), "Arial", 20);
    this->addChild(speedLabel);
    speedLabel->setPosition(Point(500, 50));
    
    distance = LabelTTF::create("0", "Arial", 24);
    this->addChild(distance);
    distance->setPosition(Point(100, visibleSize.height - distance->getContentSize().height * 2));
    return true;
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Released key code %d", keyCode);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("Key with key code %d pressed", keyCode);
}

void HelloWorld::onContinueHandler(cocos2d::Object *pSender)
{
    (callBackPointer->*continueCallBack)(pSender);
}

void HelloWorld::onPauseHandler(cocos2d::Object *pSender)
{
    (callBackPointer->*pauseCallBack)(pSender);
}

void HelloWorld::onRestartHandler(cocos2d::Object *pSender)
{
    (callBackPointer->*restartCallBack)(pSender);
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
//    keepRun::BehaviorJumpEvent *jump = new keepRun::BehaviorJumpEvent(JUMP_EVENT);
//    actor->executeEvent(jump);
//    jump = nullptr;
    (callBackPointer->*closeCallBack)(pSender);
    
    //Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}

void HelloWorld::changeMenuState(std::string stateValue)
{
    state = stateValue;
    
    if (state == GAME_STATE_WAITING_START)
    {
        continueButton->setVisible(true);
        pauseButton->setVisible(false);
        restartButton->setVisible(false);
        jumpButton->setVisible(false);
    }
    else if (state == GAME_STATE_RUNNING)
    {
        continueButton->setVisible(false);
        pauseButton->setVisible(true);
        restartButton->setVisible(false);
        jumpButton->setVisible(true);
    }
    else if (state == GAME_STATE_DEAD)
    {
        continueButton->setVisible(false);
        pauseButton->setVisible(false);
        restartButton->setVisible(true);
        jumpButton->setVisible(false);
    }
}

void HelloWorld::onUpHandler(cocos2d::Object *pSender)
{
    (callBackPointer->*upCallBack)(pSender);
}

void HelloWorld::onDownHandler(cocos2d::Object *pSender)
{
    (callBackPointer->*downCallBack)(pSender);
}