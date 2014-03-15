//
//  MSStateActor.cpp
//  Run
//
//  Created by RockLee on 14-3-10.
//
//

#include "MSStateActor.h"

NS_MS_BEGIN
/*********StateData*************/
StateData::~StateData()
{
    
}

/*********StateContext*************/
StateContext::StateContext()
{
    stateList = new moonsugar::Stack();
}

StateContext::~StateContext()
{
    delete stateList;
}

void StateContext::insertStateData(moonsugar::StateData *stateData)
{
    stateList->addItem(stateData);
    currentState = stateData;
}

void StateContext::popStateDataChangeNext()
{
    stateList->popItem();
    if (stateList->checkNext()) {
        currentState = (moonsugar::StateData *)stateList->getCurrentItem();
    }
}

void StateContext::cancelStateDataChange(moonsugar::StateData *stateData)
{
    stateList->popItem();
    insertStateData(stateData);
}

/************Behavior Event*************/
BehaviorEvent::BehaviorEvent(std::string behaviorEventType)
{
    eventType = behaviorEventType;
}

BehaviorEvent::~BehaviorEvent()
{
    
}

/*************Actor******************/
Actor::Actor()
{
    dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    stateContext = new moonsugar::StateContext();
}

Actor::~Actor()
{
    dispatcher = nullptr;
}

void Actor::executeEvent(moonsugar::BehaviorEvent *behaviorEvent)
{
    
}

NS_MS_END;