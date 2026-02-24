#include "ROS2PlayerPosePublisherNode.h"

#include "EngineUtils.h"
#include "Core/RRConversionUtils.h"

DEFINE_LOG_CATEGORY(PlayerPoseNode);

//TODO: Add vr pawn to simstate so its state can be retrieved via existing /GetEntityState service & remove this node
UROS2PlayerPosePublisherNode::UROS2PlayerPosePublisherNode()
{
    Node = CreateDefaultSubobject<UROS2NodeComponent>(TEXT("ROS2NodeComponent"));
    Node->Name = TEXT("player_pose_publisher_node");
    Node->Namespace = TEXT("ue");
    
    UE_LOG_WITH_INFO_NAMED(PlayerPoseNode, Log, TEXT("[%s][ue][Constructor] Node created"), *TopicName);
}

void UROS2PlayerPosePublisherNode::BeginPlay()
{
    Super::BeginPlay();

    Node->Init();

    ParentActor = GetOwner();

    ROS2_CREATE_LOOP_PUBLISHER_WITH_QOS(Node,
                                        this,
                                        TopicName,
                                        UROS2Publisher::StaticClass(),
                                        UROS2PoseStampedMsg::StaticClass(),
                                        PublicationFrequencyHz,
                                        &UROS2PlayerPosePublisherNode::UpdateMessage,
                                        UROS2QoS::Default,
                                        Publisher);
    
}

void UROS2PlayerPosePublisherNode::UpdateMessage(UROS2GenericMsg* InMessage)
{
    FROSPoseStamped Msg;
    const TSet<UActorComponent*>& Components = ParentActor->GetComponents();
    for (UActorComponent* Component : Components)
    {
        if (UCameraComponent* CameraComp = Cast<UCameraComponent>(Component))
        {
            FVector PlayerLocation = CameraComp->GetComponentLocation();
            PlayerLocation = PlayerLocation / 100;
            // Unreal uses left-handed Coordinate Systems, so we need to flip the y-axis
            PlayerLocation[1] = PlayerLocation[1] * -1.0; 
            FRotator PlayerOrientation = ParentActor->GetActorRotation();
            Msg.Header.FrameId = "map";
            Msg.Header.Stamp = URRConversionUtils::FloatToROSStamp(UGameplayStatics::GetTimeSeconds(GetWorld()));
            Msg.Pose.Position = PlayerLocation;
            Msg.Pose.Orientation = PlayerOrientation.Quaternion();
            CastChecked<UROS2PoseStampedMsg>(InMessage)->SetMsg(Msg);
        }
    }
    
    
}


