// Copyright 2020-2021 Rapyuta Robotics Co., Ltd.

#pragma once
// UE
#include "CoreMinimal.h"


// rclUE
#include "ROS2Subscriber.h"

#include <Msgs/ROS2Str.h>

#include "ROS2SubscriberNode.generated.h"

UCLASS()
class TURTLEBOT3_API UROS2SubscriberNode : public UActorComponent
{
    GENERATED_BODY()

public:
    UROS2SubscriberNode();

    virtual void BeginPlay() override;

    UFUNCTION()
    void MsgCallback(const UROS2GenericMsg* InMsg);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UROS2NodeComponent* Node = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TopicName = TEXT("test_topic");
};
