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
}

Actor::~Actor()
{
    dispatcher = nullptr;
}

void Actor::executeEvent(moonsugar::BehaviorEvent *behaviorEvent)
{
    
}

NS_MS_END;