#include "ROS2AudioNode.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

#include "RuntimeAudioImporterLibrary.h"
#include "Components/AudioComponent.h"
#include "Core/RRROS2GameMode.h"

#include "turtlebot3/Turtlebot3.h"

DEFINE_LOG_CATEGORY(AudioNode);

UROS2AudioNode::UROS2AudioNode()
{
    Node = CreateDefaultSubobject<UROS2NodeComponent>(TEXT("ROS2NodeComponent"));

    Node->Name = TEXT("audio_node");
    Node->Namespace = TEXT("ue_audio");
}


void UROS2AudioNode::OnAudioImporterResult(URuntimeAudioImporterLibrary* Importer, UImportedSoundWave* ImportedSoundWave, ERuntimeImportStatus Status)
{
    if (Status != ERuntimeImportStatus::SuccessfulImport)
    {
        UE_LOG_WITH_INFO_NAMED(AudioNode, Error, TEXT("Error importing audio file!"));
    }
}

void UROS2AudioNode::BeginPlay()
{
    Super::BeginPlay();
    Node->Init();
    
    ROS2_CREATE_SERVICE_SERVER(Node, this, ServiceName, UROS2TriggerSrv::StaticClass(), &UROS2AudioNode::SrvCallback);
    ROS2_CREATE_SUBSCRIBERW_WITH_QOS(Node, this, SubscriptionTopicName,UROS2AudioDataMsg::StaticClass(), &UROS2AudioNode::MsgCallback, UROS2QoS::Custom);

    StreamSoundWave = UStreamingSoundWave::CreateStreamingSoundWave();
    StreamSoundWave->PreAllocateAudioData(262144, FOnPreAllocateAudioDataResultNative::CreateWeakLambda(this, [](bool bSucceeded){}));
    StreamSoundWave->SetInitialDesiredSampleRate(RawSampleRate);
    StreamSoundWave->SetInitialDesiredNumOfChannels(RawNumChannels);

    AudioImporterLib = URuntimeAudioImporterLibrary::CreateRuntimeAudioImporter();
    AudioImporterLib->OnResultNative.AddUObject(this, &UROS2AudioNode::OnAudioImporterResult);

    this->SetSound(StreamSoundWave);

    for (AActor* Actor : TActorRange<AActor>(GetWorld()))
    {
        UE_LOG_WITH_INFO_NAMED(AudioNode, Log, TEXT("[%s][ue][Actors] %s"), *SubscriptionTopicName, *Actor->GetActorNameOrLabel());
    }
}

void UROS2AudioNode::SrvCallback(UROS2GenericSrv* InService)
{
    UROS2TriggerSrv* PlaybackTriggerService = Cast<UROS2TriggerSrv>(InService);
    StreamSoundWave->SetStopSoundOnPlaybackFinish(true);
    this->Play();
    FROSTriggerRes res;
    res.bSuccess = StreamSoundWave->IsPlaybackFinished();
    PlaybackTriggerService->SetResponse(res);
}


void UROS2AudioNode::MsgCallback(const UROS2GenericMsg* InMsg)
{
    UE_LOG_WITH_INFO_NAMED(AudioNode, Log, TEXT("[%s][ue_audio][Msg Callback] Triggered"), *SubscriptionTopicName);
    const UROS2AudioDataMsg* audioDataMsg = Cast<UROS2AudioDataMsg>(InMsg);
    if (audioDataMsg) 
    {
        FROSAudioData msg;
        audioDataMsg->GetMsg(msg);
        StreamSoundWave->AppendAudioDataFromRAW(msg.Data, RawAudioFormat, RawSampleRate, RawNumChannels);
        UE_LOG_WITH_INFO_NAMED(AudioNode, Log, TEXT("[%s][ue_audio][Msg Callback] Appended buffer"), *SubscriptionTopicName);
    }
}






