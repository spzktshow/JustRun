//
//  KRActor.cpp
//  Run
//
//  Created by RockLee on 14-3-10.
//
//

#include "KRActor.h"
#include "AnimationConfig.h"
#include "MSDataStructure.h"

NS_KR_BEGIN
/***********BehaviorEvent*********************/
BehaviorRunEvent::~BehaviorRunEvent()
{
    
}

BehaviorJumpEvent::~BehaviorJumpEvent()
{
    
}

/**********Actor**************************/
void Actor::executeEvent(moonsugar::BehaviorEvent * behaviorEvent)
{
    if (behaviorEvent->eventType == RUN_EVENT)
    {
        handlerRunEvent(behaviorEvent);
    }
    else if (behaviorEvent->eventType == JUMP_EVENT)
    {
        handlerJumpEvent(behaviorEvent);
    }
    else if (behaviorEvent->eventType == CANCEL_JUMP_EVENT)
    {
        cancelJumpEvent(behaviorEvent);
    }
}

void Actor::handlerJumpEvent(moonsugar::BehaviorEvent *jumpEvent)
{
    if (stateContext->currentState->itemName == STATE_RUN)
    {
        moonsugar::StateData * stateData = new moonsugar::StateData(STATE_JUMP);
        stateContext->insertStateData(stateData);
        //
        converToCurrent();
    }
    else if (stateContext->currentState->itemName == STATE_JUMP)
    {
        moonsugar::StateData * stateData = new moonsugar::StateData(STATE_JUMP2);
        stateContext->cancelStateDataChange(stateData);
        //
        converToCurrent();
    }
}

void Actor::cancelJumpEvent(moonsugar::BehaviorEvent *behaviorEvent)
{
    if (stateContext->currentState->itemName == STATE_JUMP || stateContext->currentState->itemName == STATE_JUMP2)
    {
        stateContext->popStateDataChangeNext();
        //
        converToCurrent();
    }
}

void Actor::handlerRunEvent(moonsugar::BehaviorEvent *runEvent)
{
    moonsugar::StateData * stateData = new moonsugar::StateData(STATE_RUN);
    stateContext->insertStateData(stateData);
    //
    converToCurrent();
}

void Actor::setPosition(cocos2d::Point pointValue)
{
    cocos2d::Point p1(pointValue.x, pointValue.y + INIT_VIEW_GAP);
    entry->view->setPosition(p1);
    entry->rect->setPosition(pointValue);
    point = pointValue;
    viewPoint = p1;
}

void Actor::pauseAction()
{
    this->isPlaying = false;
    isJumping = false;
    cocos2d::Director::getInstance()->getActionManager()->pauseTarget(this->entry->view);
}

void Actor::continueAction()
{
    cocos2d::Director::getInstance()->getActionManager()->resumeTarget(this->entry->view);
    isPlaying = true;
    isJumping = true;
}

Actor::Actor()
{
    
}

Actor::~Actor()
{
    delete entry;
}

void Actor::converToCurrent()
{
    if (!isPlaying) return;
    if (stateContext->currentState->itemName == STATE_RUN)
    {
        run();
    }
    else if (stateContext->currentState->itemName == STATE_JUMP)
    {
        jump();
    }
    else if (stateContext->currentState->itemName == STATE_JUMP2)
    {
        jump();
    }
}

void Actor::jump()
{
    entry->runAction(ANIMATION_CONFIG_JUMP01);
    startJump();
}

void Actor::onJumpComplete()
{
    cancelJumpEvent(nullptr);
}

void Actor::run()
{
    entry->runAction(ANIMATION_CONFIG_RUN01);
}

void Actor::update(float dt)
{
    if (isJumping)
    {
        cocos2d::log("%s", "Jump");
        startJumpValue = startJumpValue + gravity;
        float targetY = entry->view->getPositionY() + startJumpValue;
        float targetY1 = entry->rect->getPositionY() + startJumpValue;
        if (targetY < viewPoint.y)
        {
            targetY = viewPoint.y;
            endJump();
        }
        if (targetY1 < point.y)
        {
            targetY1 = point.y;
        }
        entry->view->setPositionY(targetY);
        entry->rect->setPositionY(targetY1);
    }
}

void Actor::startJump()
{
    isJumping = true;
    startJumpValue = JUMP_VALUE;
}

void Actor::endJump()
{
    isJumping = false;
    onJumpComplete();
}
/***************ActorEntry**********************/
ActorEntry::ActorEntry(cocos2d::Map<std::string, cocos2d::Animation *> animationDicValue, cocos2d::Sprite * viewValue, cocos2d::Sprite * rectValue)
{
    view = viewValue;
    animationDic = animationDicValue;
    rect = rectValue;
}

ActorEntry::~ActorEntry()
{
    view->release();
}

cocos2d::Animate * ActorEntry::runAction(std::string actionName)
{
    currentAction = nullptr;
    cocos2d::Animation * animation;
    cocos2d::Animate * animate;
    cocos2d::RepeatForever * repeatf;
    if (actionName == ANIMATION_CONFIG_RUN01)
    {
        animation = animationDic.at(ANIMATION_CONFIG_RUN01);
        animate = cocos2d::Animate::create(animation);
        view->stopAllActions();
        if (ANIMATION_CONFIG_RUN_LOOP == 0)
        {
            repeatf = cocos2d::RepeatForever::create(animate);
            view->runAction(repeatf);
            //
            currentAction = repeatf;
        }
        else
        {
            view->runAction(animate);
            
            currentAction = animate;
        }
    }
    else if (actionName == ANIMATION_CONFIG_JUMP01)
    {
        animation = animationDic.at(ANIMATION_CONFIG_JUMP01);
        animate = cocos2d::Animate::create(animation);
        view->stopAllActions();
        if (ANIMATION_CONFIG_JUMP_LOOP == 0)
        {
            repeatf = cocos2d::RepeatForever::create(animate);
            view->runAction(repeatf);
            
            currentAction = repeatf;
        }
        else
        {
            view->runAction(animate);
            
            currentAction = animate;
        }
    }
    return animate;
}
NS_KR_END;