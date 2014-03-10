//
//  KRActor.cpp
//  Run
//
//  Created by RockLee on 14-3-10.
//
//

#include "KRActor.h"

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
        handlerJumpEvent(behaviorEvent);
    }
    else if (behaviorEvent->eventType == JUMP_EVENT)
    {
        handlerJumpEvent(behaviorEvent);
    }
}

void Actor::handlerJumpEvent(moonsugar::BehaviorEvent *jumpEvent)
{
    keepRun::BehaviorJumpEvent *behaviorJumpEvent = static_cast<keepRun::BehaviorJumpEvent*>(jumpEvent);
    if (stateContext->currentState->itemName == STATE_RUN)
    {
        
    }
}

void Actor::handlerRunEvent(moonsugar::BehaviorEvent *runEvent)
{
    
}
NS_KR_END;