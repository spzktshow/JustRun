//
//  KRFireCircleConfig.cpp
//  Run
//
//  Created by RockLee on 14-3-12.
//
//

#include "KRFireCircleConfig.h"

NS_KR_BEGIN
/********FireCircleConfig*******************************/

FireCircleConfig::FireCircleConfig(cocos2d::ValueMap plistDicValue)
{
    if (plistDicValue.find(FIRE_CONFIG_ROUNDS) != plistDicValue.end())
    {
        cocos2d::ValueVector & vector = plistDicValue[FIRE_CONFIG_ROUNDS].asValueVector();
        for (int i = 0; i < vector.size(); i ++)
        {
            keepRun::Round * round = new keepRun::Round();
            cocos2d::ValueMap & roundMap = vector.at(i).asValueMap();
            round->roundId = roundMap.at(FIRE_CONFIG_ROUND_ID).asInt();
            round->roundName = roundMap.at(FIRE_CONFIG_ROUND_NAME).asString();
            cocos2d::ValueVector & roundGroupsVector = roundMap.at(FIRE_CONFIG_ROUND_GROUPS).asValueVector();
            cocos2d::Vector<keepRun::Group *> roundGroups;
            for (int j = 0; j < roundGroupsVector.size(); j ++)
            {
                cocos2d::ValueMap & groupMap = roundGroupsVector.at(j).asValueMap();
                keepRun::Group * group = new keepRun::Group();
                group->groupName = groupMap.at(FIRE_CONFIG_GROUP_NAME).asString();
                group->groupDistance = groupMap.at(FIRE_CONFIG_GROUP_DISTANCE).asFloat();
                cocos2d::ValueVector & groupMembersVector = groupMap.at(FIRE_CONFIG_GROUP_MEMBERS).asValueVector();
                cocos2d::Vector<keepRun::GroupMember *> groupMembers;
                for (int k = 0; k < groupMembersVector.size(); k ++)
                {
                    cocos2d::ValueMap & groupMemberMap = groupMembersVector.at(k).asValueMap();
                    keepRun::GroupMember * groupMember = new keepRun::GroupMember();
                    groupMember->circleDistance = groupMemberMap.at(FIRE_CONFIG_GROUP_MEMBER_CIRCLE_DISTANCE).asFloat();
                    groupMember->circleHigh = groupMemberMap.at(FIRE_CONFIG_GROUP_MEMBER_CIRCLE_HIGH).asFloat();
                    groupMember->circleScale = groupMemberMap.at(FIRE_CONFIG_GROUP_MEMBER_CIRCLE_SCALE).asFloat();
                    groupMembers.pushBack(groupMember);
                }
                group->groupMembers = groupMembers;
                roundGroups.pushBack(group);
            }
            round->groups = roundGroups;
            rounds.pushBack(round);
        }
        cocos2d::log("%zd", rounds.size());
    }
}

FireCircleConfig::~FireCircleConfig()
{
    
}

/********************Round****************************************/
Round::Round()
{
    
}

Round::~Round()
{
    
}

/********************GroupMember**********************************/
GroupMember::GroupMember()
{
    
}

GroupMember::~GroupMember()
{
    
}

/********************Group**********************************/
Group::Group()
{
    
}

Group::~Group()
{
    
}

NS_KR_END;