//
//  KRFireCircleConfig.h
//  Run
//  火圈配置文件
//  Created by RockLee on 14-3-12.
//
//

#ifndef __Run__KRFireCircleConfig__
#define __Run__KRFireCircleConfig__

#include "keepRun.h"

#define FIRE_CONFIG_ROUNDS          "rounds"
#define FIRE_CONFIG_ROUND_ID        "roundId"
#define FIRE_CONFIG_ROUND_NAME      "roundName"
#define FIRE_CONFIG_ROUND_GROUPS    "roundGroups"
#define FIRE_CONFIG_GROUP_NAME      "groupName"
#define FIRE_CONFIG_GROUP_SPEED     "groupSpeed"
#define FIRE_CONFIG_GROUP_DISTANCE  "groupDistance"
#define FIRE_CONFIG_GROUP_MEMBERS   "groupMembers"

#define FIRE_CONFIG_GROUP_MEMBER_CIRCLE_DISTANCE    "circleDistance"
#define FIRE_CONFIG_GROUP_MEMBER_CIRCLE_SCALE       "circleRadio"
#define FIRE_CONFIG_GROUP_MEMBER_CIRCLE_HIGH        "circleHigh"

#define FIRE_HIGH                   200

//******定义在960*640分辨率下火圈碰撞块的基础属性*****
#define FIRE_CIRCLE_WIDTH           50
#define FIRE_CIRCLE_HEIGHT          50
#define FIRE_CIRCLE_RADIO           180

NS_KR_BEGIN

class GroupMember : public cocos2d::Object
{
public:
    GroupMember();
    ~GroupMember();
    
    /******相对于小组的距离*****/
    float circleDistance;
    /*******火圈高度，根据高度和素材的比列算出scale******/
    float circleScale;
    /*******火圈相对地面的高度**************/
    float circleHigh;
};

class Group : public cocos2d::Object
{
public:
    Group();
    ~Group();
    
    std::string groupName;
    float groupSpeed;
    float groupDistance;
    cocos2d::Vector<keepRun::GroupMember *> groupMembers;
};

class Round : public cocos2d::Object
{
public:
    Round();
    ~Round();
    
    int roundId;
    std::string roundName;
    
    cocos2d::Vector<keepRun::Group *> groups;
};

class FireCircleConfig : public cocos2d::Object
{
public:
    FireCircleConfig(cocos2d::ValueMap plistDicValue);
    ~FireCircleConfig();
    
    cocos2d::Vector<keepRun::Round *> rounds;
};

NS_KR_END;

#endif /* defined(__Run__KRFireCircleConfig__) */
