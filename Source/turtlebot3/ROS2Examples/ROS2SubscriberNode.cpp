// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#include "ROS2SubscriberNode.h"

// Turtlebot3_UE
#include "turtlebot3/Turtlebot3.h"

UROS2SubscriberNode::UROS2SubscriberNode()
{
    Node = CreateDefaultSubobject<UROS2NodeComponent>(TEXT("ROS2NodeComponent"));

    // these parameters can be change from BP
    Node->Name = TEXT("subscriber_node");
    Node->Namespace = TEXT("cpp");
}

void UROS2SubscriberNode::BeginPlay()
{
    Super::BeginPlay();
    Node->Init();

    ROS2_CREATE_SUBSCRIBER(Node, this, TopicName, UROS2StrMsg::StaticClass(), &UROS2SubscriberNode::MsgCallback);
}

void UROS2SubscriberNode::MsgCallback(const UROS2GenericMsg* InMsg)
{
    const UROS2StrMsg* stringMsg = Cast<UROS2StrMsg>(InMsg);
    if (stringMsg)
    {
        FROSStr msg;
        stringMsg->GetMsg(msg);
        UE_LOG_WITH_INFO_NAMED(LogTurtlebot3, Log, TEXT("%s"), *msg.Data);
    }
}
