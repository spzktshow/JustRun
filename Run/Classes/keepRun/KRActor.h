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

/*****behavior enum*******/
#define RUN_EVENT       "runEvent"
#define JUMP_EVENT       "jumpEvent"

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

class Actor : public moonsugar::Actor
{
public:
    virtual void executeEvent(moonsugar::BehaviorEvent * behaviorEvent);
    
    void handlerJumpEvent(moonsugar::BehaviorEvent * jumpEvent);
    void handlerRunEvent(moonsugar::BehaviorEvent * runEvent);
};

NS_KR_END;

#endif /* defined(__Run__KRActor__) */
