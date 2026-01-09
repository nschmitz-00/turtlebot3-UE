#pragma once

// UE
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// rclUE
#include <ROS2Node.h>
#include <Srvs/ROS2Trigger.h>
#include <Msgs/ROS2AudioData.h>
#include "rclcUtilities.h"

#include "Sound/StreamingSoundWave.h"

#include "ROS2AudioNode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(AudioNode, Log, All);

UCLASS()
class TURTLEBOT3_API UROS2AudioNode : public USceneComponent
{
    GENERATED_BODY()

public:
    UROS2AudioNode();

    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UROS2NodeComponent* Node = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SubscriptionTopicName = TEXT("audio");

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ServiceName = TEXT("trigger_playback");

    UFUNCTION()
    void MsgCallback(const UROS2GenericMsg* InMsg);
    
    UFUNCTION()
    void SrvCallback(UROS2GenericSrv* InService);
    
    UPROPERTY()
    UAudioComponent* AudioComponent;

    UPROPERTY()
    URuntimeAudioImporterLibrary* AudioImporterLib;

    UPROPERTY()
    UStreamingSoundWave* StreamSoundWave;

    UPROPERTY(EditAnywhere)
    int32 RawSampleRate = 22050;

    UPROPERTY(EditAnywhere)
    ERuntimeRAWAudioFormat RawAudioFormat = ERuntimeRAWAudioFormat::Float32;

    UPROPERTY(EditAnywhere)
    int32 RawNumChannels = 1;

    UPROPERTY(EditAnywhere)
    ERuntimeAudioFormat AudioEncoding;
    
    UFUNCTION()
    void OnAudioImporterResult(URuntimeAudioImporterLibrary* Importer, UImportedSoundWave* ImportedSoundWave, ERuntimeImportStatus Status);    
};
