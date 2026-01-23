#pragma once
#include "CoreMinimal.h"

//rclUE
#include "HeadMountedDisplayTypes.h"
#include "Msgs/ROS2PoseStamped.h"
#include "ROS2Publisher.h"

#include "ROS2PlayerPosePublisherNode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(PlayerPoseNode, Log, All);

UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UROS2PlayerPosePublisherNode : public UActorComponent
{
    GENERATED_BODY()
    
public:
    UROS2PlayerPosePublisherNode();

    virtual void BeginPlay() override;

    UFUNCTION()
    void UpdateMessage(UROS2GenericMsg* InMessage);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UROS2NodeComponent* Node = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UROS2Publisher* Publisher = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TopicName = TEXT("player/pose");

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PublicationFrequencyHz = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* ParentActor = nullptr;
    
};
