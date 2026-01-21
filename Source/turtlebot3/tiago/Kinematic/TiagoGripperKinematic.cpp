#include "TiagoGripperKinematic.h"

ATiagoGripperKinematic::ATiagoGripperKinematic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ATiagoGripperKinematic::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }

    //Meshes
    GripperLink = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperLink"));
    GripperLeftFingerLink = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperLeftFingerLink"));
    GripperRightFingerLink = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperRightFingerLink"));
    GripperFingerMountL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerMountL"));
    GripperFingerMountR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerMountR"));
    GripperFingerL1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerL1"));
    GripperFingerR1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerR1"));
    GripperFingerR2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerR2"));

    //Joints
    GripperLink_GripperLeftFingerLink = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("GripperLink_GripperLeftFingerLink"));
    GripperLink_GripperLeftFingerLink->SetupAttachment(GripperLink);

    GripperLink_GripperRightFingerLink = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("GripperLink_GripperRightFingerLink"));
    GripperLink_GripperRightFingerLink->SetupAttachment(GripperLink);

    GripperLeftFingerLink_GripperFingerMountL = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("GripperLeftFingerLink_GripperFingerMountL"));
    GripperLeftFingerLink_GripperFingerMountL->SetupAttachment(GripperLeftFingerLink);

    GripperRightFingerLink_GripperFingerMountR = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("GripperRightFingerLink_GripperFingerMountR"));
    GripperRightFingerLink_GripperFingerMountR->SetupAttachment(GripperRightFingerLink);

    //Links
    AddLink(TEXT("gripper_link"), GripperLink);
    AddLink(TEXT("gripper_left_finger_link"), GripperLeftFingerLink);
    AddLink(TEXT("gripper_right_finger_link"), GripperRightFingerLink);
    AddLink(TEXT("gripper_finger_mount_l"), GripperFingerMountL);
    AddLink(TEXT("gripper_finger_mount_r"), GripperFingerMountR);
    AddLink(TEXT("gripper_finger_l_1"), GripperFingerL1);
    AddLink(TEXT("gripper_finger_r_1"), GripperFingerR1);
    AddLink(TEXT("gripper_finger_r_2"), GripperFingerR2);

    bBodyComponentsCreated = true;

    return true;
}

bool ATiagoGripperKinematic::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        GripperLink->SetRelativeRotation(FRotator(0, 180, 180));
        GripperLink->SetupAttachment(ArmTool);

        GripperFingerL1->SetRelativeLocation(FVector(0, -1, 0.4));
        GripperFingerL1->SetRelativeRotation(FRotator(0, 0, 0));
        GripperFingerL1->SetupAttachment(GripperFingerMountL);

        GripperFingerR1->SetRelativeLocation(FVector(2.25, -1, 0.4));
        GripperFingerR1->SetRelativeRotation(FRotator(0, 0, 0));
        GripperFingerR1->SetupAttachment(GripperFingerMountR);

        GripperFingerR2->SetRelativeLocation(FVector(-2.25, 1, 0.4));
        GripperFingerR2->SetRelativeRotation(FRotator(0 ,0, 0));
        GripperFingerR2->SetupAttachment(GripperFingerMountR);

        // ====================== Joints ==============================

        AddJoint(TEXT("gripper_link"), TEXT("gripper_left_finger_link"), TEXT("gripper_finger_joint"), GripperLink_GripperLeftFingerLink);
        AddJoint(TEXT("gripper_link"), TEXT("gripper_right_finger_link"), TEXT("gripper_right_finger_joint"), GripperLink_GripperRightFingerLink);
        AddJoint(TEXT("gripper_left_finger_link"), TEXT("gripper_finger_mount_l"), TEXT("gripper_finger_mount_l_joint"), GripperLeftFingerLink_GripperFingerMountL);
        AddJoint(TEXT("gripper_right_finger_link"), TEXT("gripper_finger_mount_r"), TEXT("gripper_finger_mount_r_joint"), GripperRightFingerLink_GripperFingerMountR);

        GripperLink_GripperLeftFingerLink->SetRelativeLocation(FVector(-3.4, 0,0));
        GripperLink_GripperLeftFingerLink->SetRelativeRotation(FRotator(0,0,0));
        GripperLink_GripperLeftFingerLink->LinearDOF = 1;
        GripperLink_GripperLeftFingerLink->RotationalDOF = 0;

        GripperLink_GripperRightFingerLink->SetRelativeLocation(FVector(3.4, 0, 0));
        GripperLink_GripperRightFingerLink->SetRelativeRotation(FRotator(0,0,0));
        GripperLink_GripperRightFingerLink->LinearDOF = 1;
        GripperLink_GripperRightFingerLink->RotationalDOF = 0;

        GripperLeftFingerLink_GripperFingerMountL->SetRelativeLocation(FVector(5, 0, -16.5));
        GripperLeftFingerLink_GripperFingerMountL->SetRelativeRotation(FRotator(0,0,0));
        GripperLeftFingerLink_GripperFingerMountL->LinearDOF = 0;
        GripperLeftFingerLink_GripperFingerMountL->RotationalDOF = 1;

        GripperRightFingerLink_GripperFingerMountR->SetRelativeLocation(FVector(-5, 0, -16.5));
        GripperRightFingerLink_GripperFingerMountR->SetRelativeRotation(FRotator(0,0,0));
        GripperRightFingerLink_GripperFingerMountR->LinearDOF = 0;
        GripperRightFingerLink_GripperFingerMountR->RotationalDOF = 1;

        GripperLeftFingerLink->SetRelativeLocation(FVector(0,0,0));
        GripperLeftFingerLink->SetRelativeRotation(FRotator(0,0,0));
        GripperLeftFingerLink->SetupAttachment(GripperLink_GripperLeftFingerLink);
        
        GripperRightFingerLink->SetRelativeLocation(FVector(0,0,0));
        GripperRightFingerLink->SetRelativeRotation(FRotator(0,0,0));
        GripperRightFingerLink->SetupAttachment(GripperLink_GripperRightFingerLink);
        
        GripperFingerMountL->SetRelativeLocation(FVector(0,0,0));
        GripperFingerMountL->SetRelativeRotation(FRotator(0,0,0));
        GripperFingerMountL->SetupAttachment(GripperLeftFingerLink_GripperFingerMountL);
        
        GripperFingerMountR->SetRelativeLocation(FVector(0,0,0));
        GripperFingerMountR->SetRelativeRotation(FRotator(0,0,0));
        GripperFingerMountR->SetupAttachment(GripperRightFingerLink_GripperFingerMountR);

        return true;
    }
    return false;
}


