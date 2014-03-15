//
//  AnimationConfig.h
//  Run
//
//  Created by RockLee on 14-3-11.
//
//

#ifndef __Run__AnimationConfig__
#define __Run__AnimationConfig__

#include "keepRun.h"
#include <vector>

#define ANIMATION_CONFIG_CONNECT    "_"
#define ANIMATION_CONFIG_CHICK      "chick"
#define ANIMATION_CONFIG_RUN01      "run_0"
#define ANIMATION_CONFIG_JUMP01     "jump_0"

//0就是无限
#define ANIMATION_CONFIG_RUN_LOOP   0
#define ANIMATION_CONFIG_JUMP_LOOP  1

#define ANIMATION_CONFIG_RUN_START  10001
#define ANIMATION_CONFIG_RUN_COUNT  20

#define ANIMATION_CONFIG_JUMP_START 10001
#define ANIMATION_CONFIG_JUMP_COUNT 33

#define ANIMATION_CONFIG_IMAGE_TYPE ".png"

#define ANIMATION_CONFIG_DELAY      0.033f

#define ANIMATION_FIRE_CIRCLE_LEFT  "2"
#define ANIMATION_FIRE_CIRCLE_RIGHT "1"
#define ANIMATION_FIRE_CIRCLE_TOTAL 8
#define ANIMATION_FIRE_CIRCLE_CONNNECT  "-"

NS_KR_BEGIN

class AnimationConfig
{
public:
    static std::vector<std::string> getRun();
    static std::vector<std::string> getJump();
    
    static cocos2d::Vector<cocos2d::SpriteFrame *> getRunForArray(cocos2d::SpriteFrameCache * cache);
    static cocos2d::Vector<cocos2d::SpriteFrame *> getJumpForArray(cocos2d::SpriteFrameCache * cache);
    
    static cocos2d::Vector<cocos2d::SpriteFrame *> getRightFireCircleForArray(cocos2d::SpriteFrameCache * cache);
    static cocos2d::Vector<cocos2d::SpriteFrame *> getLeftFireCircleForArray(cocos2d::SpriteFrameCache * cache);
    
    static cocos2d::Animation * createAnimation(cocos2d::Vector<cocos2d::SpriteFrame *> animationDatas, float delay);
};

NS_KR_END;

#endif /* defined(__Run__AnimationConfig__) */
