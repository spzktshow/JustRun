//
//  KRActor.h
//  Run
//
//  Created by RockLee on 14-3-10.
//
//

#ifndef __Run__KRActor__
#define __Run__KRActor__

#include "keepRun.h"
#include "MSStateActor.h"

/*****state enum******/
#define STATE_RUN       "run"
#define STATE_JUMP      "jump"
#define STATE_JUMP2     "jump2"

/*****behavior enum*******/
#define RUN_EVENT           "runEvent"

#define JUMP_EVENT          "jumpEvent"
#define CANCEL_JUMP_EVENT   "cancelJumpEvent"

/******************/
#define JUMP_VALUE          10
#define GRAVIRY             -.25f
#define INIT_X              200
#define INIT_Y              160
#define INIT_VIEW_GAP       40

NS_KR_BEGIN
//===========BehaviorEvent===================/
class BehaviorRunEvent : public moonsugar::BehaviorEvent
{
public:
    BehaviorRunEvent(std::string behaviorEventType):BehaviorEvent(behaviorEventType){};
    ~BehaviorRunEvent();
};

class BehaviorJumpEvent : public moonsugar::BehaviorEvent
{
public:
    BehaviorJumpEvent(std::string behaviorEventType):BehaviorEvent(behaviorEventType){};
    ~BehaviorJumpEvent();
};

/********演员实体*******/
class ActorEntry
{
public:
    //当前人物动作
    cocos2d::Action * currentAction;
    
    cocos2d::Sprite * view;
    /*****碰撞检测块******************/
    cocos2d::Sprite * rect;
    //动画数据
    cocos2d::Map<std::string, cocos2d::Animation *>  animationDic;
    
    ActorEntry(cocos2d::Map<std::string, cocos2d::Animation *> animationDicValue, cocos2d::Sprite * viewValue, cocos2d::Sprite * rectValue);
    ~ActorEntry();
    
    cocos2d::Animate * runAction(std::string actionName);
};

class Actor : public moonsugar::Actor
{
public:
    ActorEntry * entry;
    /***用于记录状态的坐标**/
    cocos2d::Point point;
    /****view point****/
    cocos2d::Point viewPoint;
    
    Actor();
    ~Actor();
    
    virtual void executeEvent(moonsugar::BehaviorEvent * behaviorEvent);
    
    void handlerJumpEvent(moonsugar::BehaviorEvent * jumpEvent);
    void cancelJumpEvent(moonsugar::BehaviorEvent * behaviorEvent);
    
    void handlerRunEvent(moonsugar::BehaviorEvent * runEvent);
    //设置初始位置
    void setPosition(cocos2d::Point pointValue);
    /******暂停当前动画*****/
    void pauseAction();
    /*******继续当前动画*****/
    void continueAction();
    
    const float gravity = GRAVIRY;
    float startJumpValue;
    
    virtual void update(float dt);
    
    bool isJumping = false;
    void startJump();
    void endJump();
    
    /****标示动画是否在播放*****/
    bool isPlaying = true;
protected:
    //将entry的状态转换到当前stateData的状态
    void converToCurrent();
    
    void jump();
    void onJumpComplete();
    
    void run();
};

NS_KR_END;

#endif /* defined(__Run__KRActor__) */
