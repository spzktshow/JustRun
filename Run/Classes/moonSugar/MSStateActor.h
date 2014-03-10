//
//  MSStateActor.h
//  Run
//
//  Created by RockLee on 14-3-10.
//
//

#ifndef __Run__MSStateActor__
#define __Run__MSStateActor__

#include <iostream>
#include "cocos2d.h"
#include <string>
#include "moonSugar.h"
#include "MSDataStructure.h"
#include "CCEventDispatcher.h"

NS_MS_BEGIN
//==========State=================/
/********标示状态的数据结构**********/
class StateData : public moonsugar::QueueItem
{
public:
    StateData(std::string itemNameValue):QueueItem(itemNameValue) {};
    ~StateData();
};

/********状态上下文数据结构，以栈形式保存状态*********/
class StateContext
{
public:
    moonsugar::Stack * stateList;
    StateData * currentState;
    
    StateContext();
    ~StateContext();
};

//==========Behavior Event============/
//行为事件
class BehaviorEvent
{
public:
	std::string eventType;
    
	BehaviorEvent(std::string behaviorEventType);
    
	~BehaviorEvent();
};

//===========Actor================/
class Actor
{
public:
    StateContext * stateContext;
    
    //listenerDispatcher
	cocos2d::EventDispatcher * dispatcher;
    
    Actor();
    ~Actor();
    
    virtual void executeEvent(moonsugar::BehaviorEvent * behaviorEvent);
};
NS_MS_END;

#endif /* defined(__Run__MSStateActor__) */
