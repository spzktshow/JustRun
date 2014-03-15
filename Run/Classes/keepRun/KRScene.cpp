//
//  KRScene.cpp
//  Run
//
//  Created by RockLee on 14-3-11.
//
//

#include "KRScene.h"
#include <math.h>
#include "AnimationConfig.h"
#include "TypeConver.h"

NS_KR_BEGIN
//========================RollScene===================================/
RollScene::RollScene(cocos2d::Layer * layerValue, float speedValue, cocos2d::SpriteFrame * spriteFrameValue, cocos2d::Rect rectValue, float frameTimeValue)
{
    layer = layerValue;
    speed = speedValue;
    spriteFrame = spriteFrameValue;
    rect = rectValue;
    frameTime = frameTimeValue;
    //
    componentCount = calculateComponentsCount();
}

RollScene::~RollScene()
{
    
}

void RollScene::roll()
{
    for (int i = 0; i < tiles.size(); i ++)
    {
        keepRun::RollTile * tile = tiles.at(i);
        tile->roll();
    }
}

int RollScene::calculateComponentsCount()
{
    return ceil(rect.size.width / spriteFrame->getRect().size.width) + 1;
}

void RollScene::tile()
{
    for (int i = 0; i < componentCount; i ++)
    {
        cocos2d::Sprite * tempSprite = cocos2d::Sprite::createWithSpriteFrame(spriteFrame);
        keepRun::RollTile * rollTile = new keepRun::RollTile(tempSprite, rect, speed, frameTime);
        rollTile->rowDirect = true;
        tiles.pushBack(rollTile);
        layer->addChild(tempSprite);
        tempSprite->setPosition(i * (spriteFrame->getRect().size.width), 0);
    }
}

void RollScene::pause()
{
    isRolling = false;
}

void RollScene::update(float dt)
{
    if (isRolling)
    {
        for (int i = 0; i < tiles.size(); i ++)
        {
            keepRun::RollTile * tile = tiles.at(i);
            tile->move(dt);
        }
    }
}

void RollScene::start()
{
    isRolling = true;
}

void RollScene::upSpeed()
{
    speed += SCENE_ADD_SPEED;
    for (int i = 0; i < tiles.size(); i ++)
    {
        keepRun::RollTile * tile = tiles.at(i);
        tile->speed = speed;
    }
}

void RollScene::downSpeed()
{
    speed -= SCENE_ADD_SPEED;
    for (int i = 0; i < tiles.size(); i ++)
    {
        keepRun::RollTile * tile = tiles.at(i);
        tile->speed = speed;
    }
}
//=========================RollTile====================================/
RollTile::RollTile(cocos2d::Sprite * viewValue, cocos2d::Rect rectValue, float speedValue, float frameTimeValue)
{
    view = viewValue;
    rect = rectValue;
    speed = speedValue;
    frameTime = frameTimeValue;
}

RollTile::~RollTile()
{
    
}

void RollTile::roll()
{
    float time = calcualteAnimationDuration();
    float targetX = 0 - (view->getTextureRect().size.width - speed * 10);
    cocos2d::Action * action = cocos2d::MoveTo::create(time, cocos2d::Point(targetX, view->getPositionY()));
    cocos2d::CallFunc * callBack = cocos2d::CallFunc::create(CC_CALLBACK_0(RollTile::onRollComplete, this));
    cocos2d::FiniteTimeAction * sq = cocos2d::Sequence::create(static_cast<cocos2d::FiniteTimeAction*>(action), callBack, NULL);
    view->runAction(sq);
}

void RollTile::onRollComplete()
{
    view->stopAllActions();
    view->setPositionX(view->getTextureRect().size.width - speed * 10);
    float time = calcualteAnimationDuration();
    //cocos2d::log("time %f", time);
    float targetX = 0 - (view->getTextureRect().size.width - speed * 10);
    cocos2d::Action * action = cocos2d::MoveTo::create(time, cocos2d::Point(targetX, view->getPositionY()));
    cocos2d::CallFunc * callBack = cocos2d::CallFunc::create(CC_CALLBACK_0(RollTile::onRollComplete, this));
    cocos2d::FiniteTimeAction * sq = cocos2d::Sequence::create(static_cast<cocos2d::FiniteTimeAction*>(action), callBack, NULL);
    view->runAction(sq);
}

float RollTile::calcualteAnimationDuration()
{
    float targetX = 0 - (view->getTextureRect().size.width - speed * 10);
    float distance = view->getPositionX() - targetX;
    float time = distance / speed * frameTime;
    return time;
}

void RollTile::move(float dt)
{
    float target;
    float gap;
    if (rowDirect)
    {
        target = 0 - view->getTextureRect().size.width;
        if (view->getPositionX() <= target)
        {
            gap = view->getPositionX() - target;
            view->setPositionX(view->getTextureRect().size.width + gap);
        }
        view->setPositionX(view->getPositionX() - speed);
    }
    else
    {
        target = view->getTextureRect().size.width;
        
        if (view->getPositionX() >= target)
        {
            gap = view->getPositionX() - target;
            view->setPositionX(0 - view->getTextureRect().size.width + gap + speed);
        }
        view->setPositionX(view->getPositionX() + speed);
    }
}
//===============FireCircle=======================/
FireCircle::~FireCircle()
{
    groupMember = nullptr;
}

void FireCircle::onRollComplete()
{
    if (rollCompleteCallBack && rollCompleteCallBackTarget)
    {
        (rollCompleteCallBackTarget->*rollCompleteCallBack)(this);
    }
}

void FireCircle::move(float dt)
{
    cocos2d::log("%f", dt);
    float target;
    if (rowDirect)
    {
        target = 0 - view->getTextureRect().size.width;
        if (view->getPositionX() <= target)
        {
            onRollComplete();
            return;
        }
        view->setPositionX(view->getPositionX() - speed);
        view2->setPositionX(view->getPositionX());
        leftFireCircleView->setPositionX(leftFireCircleView->getPositionX() - speed);
        rightFireCircleView->setPositionX(rightFireCircleView->getPositionX() - speed);
    }
    else
    {
        target = view->getTextureRect().size.width;
        if (view->getPositionX() >= target)
        {
            onRollComplete();
            return;
        }
        view->setPositionX(view->getPositionX() + speed);
        view2->setPositionX(view->getPositionX());
        leftFireCircleView->setPositionX(leftFireCircleView->getPositionX() + speed);
        rightFireCircleView->setPositionX(rightFireCircleView->getPositionX() + speed);
    }
}
//===============FireCircleScene===================/
FireCircleScene::FireCircleScene(keepRun::FireCircleConfig * fireCircleConfigValue, cocos2d::Layer * layerValue,
                                 cocos2d::SpriteFrame * rectSpriteFrameValue,
                                 cocos2d::Rect rectValue,
                                 float frameTimeValue, cocos2d::Layer * leftLayerValue, cocos2d::Layer * rightLayerValue, cocos2d::Vector<cocos2d::SpriteFrame *> leftAnimationValue, cocos2d::Vector<cocos2d::SpriteFrame *> rightAnimationValue)
{
    layer = layerValue;
    frameTime = frameTimeValue;
    rectSpriteFrame = rectSpriteFrameValue;
    rect = rectValue;
    fireCircleConfig = fireCircleConfigValue;
    
    leftLayer = leftLayerValue;
    rightLayer = rightLayerValue;
    
    leftAnimations = leftAnimationValue;
    rightAnimations = rightAnimationValue;
}

FireCircleScene::~FireCircleScene()
{
    
}

void FireCircleScene::roll()
{
    
}

bool FireCircleScene::upSpeed()
{
    if (currentSpeed < SCENE_MAX_SPEED)
    {
        currentSpeed += SCENE_ADD_SPEED;
        for (int i = 0; i < checkList.size(); i ++)
        {
            keepRun::FireCircle * node = checkList.at(i);
            node->speed = currentSpeed;
        }
        return true;
    }
    return false;
}

bool FireCircleScene::downSpeed()
{
    if (currentSpeed > SCENE_MIN_SPEED)
    {
        currentSpeed -= SCENE_ADD_SPEED;
        for (int i = 0; i < checkList.size(); i ++)
        {
            keepRun::FireCircle * node = checkList.at(i);
            node->speed = currentSpeed;
        }
        return true;
    }
    return false;
}

void FireCircleScene::onFireCircleEndCallBack(keepRun::FireCircle * fireCircle)
{
    checkList.eraseObject(fireCircle);
    fireCircle->view->getParent()->removeChild(fireCircle->view);
    fireCircle->view2->getParent()->removeChild(fireCircle->view2);
    fireCircle->leftFireCircleView->getParent()->removeChild(fireCircle->leftFireCircleView);
    fireCircle->rightFireCircleView->getParent()->removeChild(fireCircle->rightFireCircleView);
    fireCircle->release();
    //cocos2d::log("%s", "a firecircle be realse");
}

void FireCircleScene::rollStep(float dt)
{
    //检测round
    if (currentRunRoundIndex == -1)//新开始
    {
        currentRunRoundIndex ++;
        //查找下一个round
        getNextRound();
    }
    else if (currentRound == nullptr)//currentRunRoundId所保存的round已经结束
    {
        currentRunRoundIndex ++;
        //查找下一个round
        getNextRound();
        //
        currentGroupIndex = -1;
    }
    //检测group
    if (currentGroupIndex == -1)
    {
        currentGroupIndex ++;
        
        currentGroup = getNextGroup();
    }
    else if (currentGroup == nullptr)
    {
        currentGroupIndex ++;
        
        currentGroup = getNextGroup();
    }
    if (currentGroup == nullptr)//group结束
    {
        //
        currentRound = nullptr;
        return;
    }
    else
    {
        if (currentMemberIndex == -1)
        {
            currentMemberIndex ++;
            
            currentGroupMember = getNextGroupMember();
        }
        else if (currentGroupMember == nullptr)
        {
            currentMemberIndex ++;
            
            currentGroupMember = getNextGroupMember();
        }
        
        if (currentGroupMember == nullptr)
        {
            currentGroup = nullptr;
            currentMemberIndex = -1;
            return;
        }
        else
        {
            if (hadRunDistance >= currentGroup->groupDistance + currentGroupMember->circleDistance + rect.size.width)
            {
                cocos2d::Sprite * bottom = cocos2d::Sprite::createWithSpriteFrame(rectSpriteFrame);
                cocos2d::Sprite * top = cocos2d::Sprite::createWithSpriteFrame(rectSpriteFrame);
                keepRun::FireCircle * fireCircle = new keepRun::FireCircle(top, bottom, rect, currentSpeed, ANIMATION_CONFIG_DELAY,currentGroupMember, rectSpriteFrame);
                fireCircle->rollCompleteCallBack = cocos2d::SEL_CallFuncO(&FireCircleScene::onFireCircleEndCallBack);
                fireCircle->rollCompleteCallBackTarget = this;
                fireCircle->rowDirect = true;
                layer->addChild(bottom);
                layer->addChild(top);
                top->setPositionX(hadRunDistance - currentGroup->groupDistance - currentGroupMember->circleDistance);
                bottom->setPositionX(hadRunDistance - currentGroup->groupDistance - currentGroupMember->circleDistance);
                //width && height
                float targetHeight = calculateHitRectHeight(currentGroupMember);
                float heightScale = calculateScale(targetHeight, top->getTextureRect().size.height);
                float widthScale = calculateScale(FIRE_CIRCLE_WIDTH, top->getTextureRect().size.width);
                top->setScaleY(heightScale);
                top->setScaleX(widthScale);
                bottom->setScaleY(heightScale);
                bottom->setScaleX(widthScale);
                //y
                //bottom
                float gap = currentGroupMember->circleHigh - currentGroupMember->circleScale;
                bottom->setPositionY(gap + targetHeight * .5 + SCENE_ROAD_Y);
                top->setPositionY(gap + currentGroupMember->circleScale * 2 - targetHeight * .5 + SCENE_ROAD_Y);
                
                //leftFireCircle
                float circleScale = calculateScale(currentGroupMember->circleScale, FIRE_CIRCLE_RADIO);
                auto leftFireCircle = cocos2d::Sprite::create();
                cocos2d::Animation * leftAnimation = keepRun::AnimationConfig::createAnimation(leftAnimations, ANIMATION_CONFIG_DELAY);
                cocos2d::Animate * leftAnimate = cocos2d::Animate::create(leftAnimation);
                cocos2d::RepeatForever * leftRepeat = cocos2d::RepeatForever::create(leftAnimate);
                leftFireCircle->runAction(leftRepeat);
                leftLayer->addChild(leftFireCircle);
                leftFireCircle->setPositionY(currentGroupMember->circleHigh + SCENE_ROAD_Y);
                leftFireCircle->setPositionX(hadRunDistance - currentGroup->groupDistance - currentGroupMember->circleDistance);
                leftFireCircle->setScaleY(circleScale);
                //rightFireCircle
                auto rightFireCircle = cocos2d::Sprite::create();
                cocos2d::Animation * rightAnimation = keepRun::AnimationConfig::createAnimation(rightAnimations, ANIMATION_CONFIG_DELAY);
                cocos2d::Animate * rightAnimate = cocos2d::Animate::create(rightAnimation);
                cocos2d::RepeatForever * rightRepeat = cocos2d::RepeatForever::create(rightAnimate);
                rightFireCircle->runAction(rightRepeat);
                rightLayer->addChild(rightFireCircle);
                rightFireCircle->setPositionY(currentGroupMember->circleHigh + SCENE_ROAD_Y);
                rightFireCircle->setPositionX(hadRunDistance - currentGroup->groupDistance - currentGroupMember->circleDistance);
                rightFireCircle->setScaleY(circleScale);
                fireCircle->leftFireCircleView = leftFireCircle;
                fireCircle->rightFireCircleView = rightFireCircle;
                checkList.pushBack(fireCircle);
                currentGroupMember = nullptr;
            }
        }
    }
    hadRunDistance += currentSpeed;
    viewDistance += currentSpeed;
    currentFrames ++;
    if (currentFrames >= 60)
    {
        currentFrames = 0;
        distance->setString(moonsugar::TypeConver::intToString(viewDistance));
    }
}

float FireCircleScene::calculateHitRectHeight(keepRun::GroupMember * groupMemberValue)
{
    //
    return groupMemberValue->circleScale * FIRE_CIRCLE_HEIGHT / FIRE_CIRCLE_RADIO;
}

float FireCircleScene::calculateScale(float targetValue, float value)
{
    return targetValue / value;
}

void FireCircleScene::destoryAllFireCircle()
{
    while(checkList.size() > 0)
    {
        keepRun::FireCircle * node = checkList.at(0);
        onFireCircleEndCallBack(node);
    }
}

void FireCircleScene::restart()
{
    destoryAllFireCircle();
    
    currentRunRoundIndex = -1;
    currentGroupIndex = -1;
    currentMemberIndex = -1;
    currentRound = nullptr;
    currentGroup = nullptr;
    currentGroupMember = nullptr;
    hadRunDistance = 0;
    viewDistance = 0;
    
    currentFrames = 0;
    distance->setString(moonsugar::TypeConver::intToString(hadRunDistance));
    
    isRolling = true;
}

void FireCircleScene::start()
{
    isRolling = true;
    for (int i = 0; i < checkList.size(); i ++)
    {
        keepRun::FireCircle * fireCircle = checkList.at(i);
        cocos2d::Director::getInstance()->getActionManager()->resumeTarget(fireCircle->leftFireCircleView);
        cocos2d::Director::getInstance()->getActionManager()->resumeTarget(fireCircle->rightFireCircleView);
    }
}

void FireCircleScene::pause()
{
    isRolling = false;
    for (int i = 0; i < checkList.size(); i ++)
    {
        keepRun::FireCircle * fireCircle = checkList.at(i);
        cocos2d::Director::getInstance()->getActionManager()->pauseTarget(fireCircle->leftFireCircleView);
        cocos2d::Director::getInstance()->getActionManager()->pauseTarget(fireCircle->rightFireCircleView);
    }
}

void FireCircleScene::update(float dt)
{
    rollStep(dt);
    //
    for (int i = 0; i < checkList.size(); i ++)
    {
        keepRun::FireCircle * node = checkList.at(i);
        cocos2d::Rect nodeRect = node->view->getBoundingBox();
        if (nodeRect.intersectsRect(actor->entry->rect->getBoundingBox()) || node->view2->getBoundingBox().intersectsRect(actor->entry->rect->getBoundingBox()))
        {
            cocos2d::log("%s", "碰撞拉");
            if (callBackPointer && onHitHandler)
            {
                (callBackPointer->*onHitHandler)();
            }
            //
            return;
        }
        node->move(dt);
    }
}

keepRun::Round * FireCircleScene::getNextRound()
{
    if (fireCircleConfig->rounds.size() > currentRunRoundIndex)
    {
        currentRound = fireCircleConfig->rounds.at(currentRunRoundIndex);
        return currentRound;
    }
    else
    {
        hadRunDistance = 0;
        currentRound = fireCircleConfig->rounds.at(fireCircleConfig->rounds.size() - 1);
        return currentRound;
    }
}

keepRun::Group * FireCircleScene::getNextGroup()
{
    if (currentRound->groups.size() > currentGroupIndex)
    {
        currentGroup = currentRound->groups.at(currentGroupIndex);
        return currentGroup;
    }
    return nullptr;
}

keepRun::GroupMember * FireCircleScene::getNextGroupMember()
{
    if (currentGroup->groupMembers.size() > currentMemberIndex)
    {
        currentGroupMember = currentGroup->groupMembers.at(currentMemberIndex);
        return currentGroupMember;
    }
    return nullptr;
}

NS_KR_END;