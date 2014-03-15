//
//  KRScene.h
//  Run
//
//  Created by RockLee on 14-3-11.
//
//

#ifndef __Run__KRScene__
#define __Run__KRScene__

#include "keepRun.h"
#include "KRFireCircleConfig.h"
#include "KRActor.h"

#define SCENE_ROAD_Y        80
#define SCENE_TILE_GAP      100
#define SCENE_INIT_SPEED    8
//加速度
#define SCENE_ADD_SPEED     2
#define SCENE_MAX_SPEED     20
#define SCENE_MIN_SPEED     8

NS_KR_BEGIN
/*****滚动场景*********/
class RollTile : public cocos2d::Object
{
public:
    RollTile(cocos2d::Sprite * viewValue, cocos2d::Rect rectValue, float speedValue, float frameTimeValue);
    ~RollTile();
    
    cocos2d::Sprite * view;
    cocos2d::Rect rect;
    float speed;
    float frameTime;
    
    virtual void roll();
    virtual void onRollComplete();
    /******移动******/
    virtual void move(float dt);
    /********行方向, true=right false=left**********/
    bool rowDirect;
protected:
    virtual float calcualteAnimationDuration();
};

class FireCircle : public keepRun::RollTile
{
public:
    FireCircle(cocos2d::Sprite * viewValue
               , cocos2d::Sprite * viewValue2
               , cocos2d::Rect rectValue
               , float speedValue
               , float frameTimeValue
               , keepRun::GroupMember * groupMemberValue
               , cocos2d::SpriteFrame * rectSpriteFrameValue
               )
    :RollTile(viewValue, rectValue, speedValue, frameTimeValue) {
        groupMember = groupMemberValue;
        rectSpriteFrame = rectSpriteFrameValue;
        view2 = viewValue2;
    };
    ~FireCircle();
    
    //config
    keepRun::GroupMember * groupMember;
    
    virtual void onRollComplete();
    
    /*****定义为前景火圈
     super的view定义为后景火圈
     *****/
    cocos2d::Sprite * view2;
    
    cocos2d::Sprite * leftFireCircleView;
    cocos2d::Sprite * rightFireCircleView;
    
    cocos2d::SpriteFrame * rectSpriteFrame;
    
    cocos2d::Object * rollCompleteCallBackTarget;
    cocos2d::SEL_CallFuncO rollCompleteCallBack;
    
    /******移动******/
    virtual void move(float dt);
    /********行方向, true=right false=left**********/
    bool rowDirect;
};

class FireCircleScene : public cocos2d::Object
{
public:
    FireCircleScene(keepRun::FireCircleConfig * fireCircleConfigValue, cocos2d::Layer * layerValue, cocos2d::SpriteFrame * rectSpriteFrameValue, cocos2d::Rect rectvalue, float frameTimeValue, cocos2d::Layer * leftLayer, cocos2d::Layer * rightLayer, cocos2d::Vector<cocos2d::SpriteFrame *> leftAnimationValue, cocos2d::Vector<cocos2d::SpriteFrame *> rightAnimationValue);
    ~FireCircleScene();
    
    cocos2d::Layer * layer;
    cocos2d::Layer * leftLayer;
    cocos2d::Layer * rightLayer;
    cocos2d::Vector<cocos2d::SpriteFrame *> leftAnimations;
    cocos2d::Vector<cocos2d::SpriteFrame *> rightAnimations;
    float frameTime;
    cocos2d::SpriteFrame * rectSpriteFrame;
    cocos2d::Rect rect;
    keepRun::FireCircleConfig * fireCircleConfig;
    
    virtual void roll();
    /*****这个是计时器用来调用的方法******/
    virtual void rollStep(float dt);
    /***********这个是每帧调用的update**************/
    virtual void update(float dt);
    
    virtual void onFireCircleEndCallBack(keepRun::FireCircle *);
    
    /********待碰撞列表*************/
    cocos2d::Vector<keepRun::FireCircle *> checkList;
    /******用来判断，小鸡的碰撞*******/
    keepRun::Actor * actor;
    
    /*********滚动********/
    bool isRolling;
    /*********暂停********/
    virtual void pause();
    /*********开始********/
    virtual void start();
    /*********重新开始*******/
    virtual void restart();
    /*********销毁所有现在场景上的fireCircle*********/
    void destoryAllFireCircle();
    
    cocos2d::SEL_CallFunc onHitHandler;
    cocos2d::Object * callBackPointer;
    
    /****当前运行的关卡******/
    int currentRunRoundIndex = -1;
    keepRun::Round * currentRound;
    /****当前运行的组*******/
    int currentGroupIndex = -1;
    keepRun::Group * currentGroup;
    /****当前运行的成员******/
    int currentMemberIndex = -1;
    keepRun::GroupMember * currentGroupMember;
    //这个数值用来计算跑到已经滚动的距离
    float hadRunDistance = 0;
    float viewDistance = 0;
    
    //当前速度
    float currentSpeed = SCENE_INIT_SPEED;
    
    bool upSpeed();
    bool downSpeed();
    
    cocos2d::LabelTTF * distance;
    int currentFrames;
protected:
    virtual keepRun::Round * getNextRound();
    virtual keepRun::Group * getNextGroup();
    virtual keepRun::GroupMember * getNextGroupMember();
    
    /*******根据当前半径与标准半径的比值算出碰撞块的高度*************/
    virtual float calculateHitRectHeight(keepRun::GroupMember * groupMemberValue);
    /*******根据目标值和当前值算出scale值***********************/
    virtual float calculateScale(float targetValue, float value);
};

class RollScene
{
public:
    RollScene(cocos2d::Layer * layerValue, float speedValue, cocos2d::SpriteFrame * spriteFrameValue, cocos2d::Rect rectValue, float frameTimeValue);
    ~RollScene();
    
    cocos2d::Layer * layer;
    float speed;
    float frameTime;
    cocos2d::SpriteFrame * spriteFrame;
    cocos2d::Rect rect;
    
    /*********滚动********/
    bool isRolling;
    
    void roll();
    
    void update(float dt);
    /*******平铺组件********/
    virtual void tile();
    /*********暂停********/
    virtual void pause();
    /*********开始********/
    virtual void start();
    
    void upSpeed();
    void downSpeed();
protected:
    /***需要填充屏幕的组件数量**/
    int componentCount;
    /***填充组件列表，按顺序排列****/
    cocos2d::Vector<RollTile *> tiles;
    /***********
     计算在当前rect下，需要多少个spriteFrameValue能够填充滚动屏幕洗
     算法为 ceil(rect.size.width / spriteFrameValue.width) + 1;
     ***/
    virtual int calculateComponentsCount();
};

NS_KR_END;

#endif /* defined(__Run__KRScene__) */
