#include "ROS2PlayerPosePublisherNode.h"

#include "EngineUtils.h"

DEFINE_LOG_CATEGORY(PlayerPoseNode);

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
                                        UROS2PoseMsg::StaticClass(),
                                        PublicationFrequencyHz,
                                        &UROS2PlayerPosePublisherNode::UpdateMessage,
                                        UROS2QoS::Default,
                                        Publisher);
    
}

void UROS2PlayerPosePublisherNode::UpdateMessage(UROS2GenericMsg* InMessage)
{
    FROSPose Msg;
    FVector PlayerLocation = ParentActor->GetActorLocation();
    PlayerLocation = PlayerLocation / 100;
    FRotator PlayerOrientation = ParentActor->GetActorRotation();
    Msg.Position = PlayerLocation;
    Msg.Orientation = PlayerOrientation.Quaternion();
    CastChecked<UROS2PoseMsg>(InMessage)->SetMsg(Msg);
}


