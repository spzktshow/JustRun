//
//  AnimationConfig.cpp
//  Run
//
//  Created by RockLee on 14-3-11.
//
//

#include "AnimationConfig.h"
#include "TypeConver.h"

NS_KR_BEGIN

std::vector<std::string> AnimationConfig::getRun()
{
    std::string chick = ANIMATION_CONFIG_CHICK;
    std::string connect = ANIMATION_CONFIG_CONNECT;
    std::string action = ANIMATION_CONFIG_RUN01;
    std::string imageType = ANIMATION_CONFIG_IMAGE_TYPE;
    std::vector<std::string> list;
    for (int i = 0; i < ANIMATION_CONFIG_RUN_COUNT; i++) {
        std::string name = chick + connect + action;
        std::string index = moonsugar::TypeConver::intToString(ANIMATION_CONFIG_RUN_START + i);
        name += index;
        name += imageType;
        list.push_back(name);
        //cocos2d::log("%s", name.c_str());
    }
    return list;
}

std::vector<std::string> AnimationConfig::getJump()
{
    std::string chick = ANIMATION_CONFIG_CHICK;
    std::string connect = ANIMATION_CONFIG_CONNECT;
    std::string action = ANIMATION_CONFIG_JUMP01;
    std::string imageType = ANIMATION_CONFIG_IMAGE_TYPE;
    std::vector<std::string> list;
    for (int i = 0; i < ANIMATION_CONFIG_JUMP_COUNT; i++) {
        std::string name = chick + connect + action;
        std::string index = moonsugar::TypeConver::intToString(ANIMATION_CONFIG_JUMP_START + i);
        name += index;
        name += imageType;
        list.push_back(name);
        //cocos2d::log("%s", name.c_str());
    }
    return list;
}

cocos2d::Vector<cocos2d::SpriteFrame *> AnimationConfig::getRunForArray(cocos2d::SpriteFrameCache * cache)
{
    std::string chick = ANIMATION_CONFIG_CHICK;
    std::string connect = ANIMATION_CONFIG_CONNECT;
    std::string action = ANIMATION_CONFIG_RUN01;
    std::string imageType = ANIMATION_CONFIG_IMAGE_TYPE;
    cocos2d::Vector<cocos2d::SpriteFrame *> list;
    cocos2d::SpriteFrame * spriteFrame;
    for (int i = 0; i < ANIMATION_CONFIG_RUN_COUNT; i++) {
        std::string name = chick + connect + action;
        std::string index = moonsugar::TypeConver::intToString(ANIMATION_CONFIG_RUN_START + i);
        name += index;
        name += imageType;
        spriteFrame = cache->getSpriteFrameByName(name);
        list.pushBack(spriteFrame);
    }
    return list;
}

cocos2d::Vector<cocos2d::SpriteFrame *> AnimationConfig::getJumpForArray(cocos2d::SpriteFrameCache * cache)
{
    std::string chick = ANIMATION_CONFIG_CHICK;
    std::string connect = ANIMATION_CONFIG_CONNECT;
    std::string action = ANIMATION_CONFIG_JUMP01;
    std::string imageType = ANIMATION_CONFIG_IMAGE_TYPE;
    cocos2d::SpriteFrame * spriteFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *>list;
    for (int i = 0; i < ANIMATION_CONFIG_JUMP_COUNT; i++) {
        std::string name = chick + connect + action;
        std::string index = moonsugar::TypeConver::intToString(ANIMATION_CONFIG_JUMP_START + i);
        name += index;
        name += imageType;
        spriteFrame = cache->getSpriteFrameByName(name);
        list.pushBack(spriteFrame);
    }
    return list;
}

cocos2d::Vector<cocos2d::SpriteFrame *> AnimationConfig::getLeftFireCircleForArray(cocos2d::SpriteFrameCache *cache)
{
    cocos2d::Vector<cocos2d::SpriteFrame *> list;
    for (int i = 0; i < ANIMATION_FIRE_CIRCLE_TOTAL; i++)
    {
        std::string name = moonsugar::TypeConver::intToString(i + 1);
        name += ANIMATION_FIRE_CIRCLE_CONNNECT;
        name += ANIMATION_FIRE_CIRCLE_LEFT;
        name += ANIMATION_CONFIG_IMAGE_TYPE;
        auto spriteFrame = cache->getSpriteFrameByName(name);
        list.pushBack(spriteFrame);
    }
    return list;
}

cocos2d::Vector<cocos2d::SpriteFrame *> AnimationConfig::getRightFireCircleForArray(cocos2d::SpriteFrameCache *cache)
{
    cocos2d::Vector<cocos2d::SpriteFrame *> list;
    for (int i = 0; i < ANIMATION_FIRE_CIRCLE_TOTAL; i++)
    {
        std::string name = moonsugar::TypeConver::intToString(i + 1);
        name += ANIMATION_FIRE_CIRCLE_CONNNECT;
        name += ANIMATION_FIRE_CIRCLE_RIGHT;
        name += ANIMATION_CONFIG_IMAGE_TYPE;
        auto spriteFrame = cache->getSpriteFrameByName(name);
        list.pushBack(spriteFrame);
    }
    return list;
}

cocos2d::Animation * AnimationConfig::createAnimation(cocos2d::Vector<cocos2d::SpriteFrame *> animationDatas, float delay)
{
    cocos2d::Animation * animation = cocos2d::Animation::createWithSpriteFrames(animationDatas, delay);
    return animation;
}

NS_KR_END;