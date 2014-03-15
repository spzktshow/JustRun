#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "KRActor.h"
#include "KRScene.h"

#define GAME_STATE_RUNNING          "running"
#define GAME_STATE_DEAD             "dead"
#define GAME_STATE_WAITING_START    "waitingStart"

/*****这层是ui层********/
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    void onContinueHandler(Object* pSender);
    void onPauseHandler(Object* pSender);
    void onRestartHandler(Object* pSender);
    void onUpHandler(Object * pSender);
    void onDownHandler(Object * pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    /*****ui层执行回调的函数所在的类的指针*********/
    cocos2d::Object * callBackPointer;
    //关闭按钮调用的回调函数
    cocos2d::SEL_CallFuncO closeCallBack;
    //暂停按钮调用的回调函数
    cocos2d::SEL_CallFuncO pauseCallBack;
    //继续按钮调用的回调函数
    cocos2d::SEL_CallFuncO continueCallBack;
    //重新开始按钮调用的回调函数
    cocos2d::SEL_CallFuncO restartCallBack;
    //up button
    cocos2d::SEL_CallFuncO downCallBack;
    //down button
    cocos2d::SEL_CallFuncO upCallBack;
    
    cocos2d::MenuItemImage * continueButton;
    cocos2d::MenuItemImage * pauseButton;
    cocos2d::MenuItemImage * restartButton;
    cocos2d::MenuItemImage * jumpButton;
    cocos2d::MenuItemImage * upButton;
    cocos2d::MenuItemImage * downbutton;
    
    /****转换当前button menuState*******/
    std::string state;
    void changeMenuState(std::string stateValue);
    
    //速度label
    cocos2d::LabelTTF * speedLabel;
    //距离label
    cocos2d::LabelTTF * distance;
};

class MainScene : public cocos2d::Scene
{
public:
    static MainScene * create();
    
    virtual bool init();
    /*****火圈场景控制器*****/
    keepRun::FireCircleScene * fireCircleScene;
    keepRun::RollScene * roadScene;
    keepRun::RollScene * shanRollScene;
    keepRun::RollScene * layer1RollScene;
    keepRun::RollScene * layer2RollScene;
    keepRun::RollScene * layer3RollScene;
    
    virtual void update(float dt);
    
    keepRun::Actor * actor;
    
    //关闭事件
    void onCloseCallBack(Object * pSender);
    //暂停事件
    void onPauseCallBack(Object * obj);
    //继续事件
    void onContinueCallBack(Object * obj);
    //重新开始事件
    void onRestartCallBack(Object *obj);
    //加速
    void onUpCallBack(Object *obj);
    //减速
    void onDownCallBack(Object * obj);
    
    HelloWorld * uiLayer;
    /****碰撞回调*******/
    void onHitHandler();
    
    virtual void onEnter();
};

#endif // __HELLOWORLD_SCENE_H__
