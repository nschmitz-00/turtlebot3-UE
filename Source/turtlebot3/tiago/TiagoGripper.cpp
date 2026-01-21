#include "TiagoGripper.h"

#include "NavigationSystemTypes.h"

ATiagoGripper::ATiagoGripper(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ATiagoGripper::SetupBody()
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

    //Constraints
    ArmTool_GripperLink = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("ArmTool_GripperLink"));
    //ArmTool_GripperLink->SetupAttachment(ArmTool);

    GripperFingerMountL_GripperFingerL1 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("GripperFingerMountL_GripperFingerL1"));
    //GripperFingerMountL_GripperFingerL1->SetupAttachment(GripperFingerMountL);

    GripperFingerMountR_GripperFingerR1 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("GripperFingerMountR_GripperFingerR1"));
    //GripperFingerMountR_GripperFingerR1->SetupAttachment(GripperFingerMountR);

    GripperFingerMountR_GripperFingerR2 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("GripperFingerMountR_GripperFingerR2"));
    //GripperFingerMountR_GripperFingerR2->SetupAttachment(GripperFingerMountR);

    //Joints
    GripperLink_GripperLeftFingerLink = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("GripperLink_GripperLeftFingerLink"));
    GripperLink_GripperLeftFingerLink->SetupAttachment(GripperLink);

    GripperLink_GripperRightFingerLink = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("GripperLink_GripperRightFingerLink"));
    GripperLink_GripperRightFingerLink->SetupAttachment(GripperLink);

    GripperLeftFingerLink_GripperFingerMountL = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("GripperLeftFingerLink_GripperFingerMountL"));
    GripperLeftFingerLink_GripperFingerMountL->SetupAttachment(GripperLeftFingerLink);

    GripperRightFingerLink_GripperFingerMountR = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("GripperRightFingerLink_GripperFingerMountR"));
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

bool ATiagoGripper::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        // ======================== Physic settings ====================

        GripperLink->SetSimulatePhysics(true);
        GripperLeftFingerLink->SetSimulatePhysics(true);
        GripperRightFingerLink->SetSimulatePhysics(true);
        GripperFingerMountL->SetSimulatePhysics(true);
        GripperFingerMountR->SetSimulatePhysics(true);
        GripperFingerL1->SetSimulatePhysics(true);
        GripperFingerR1->SetSimulatePhysics(true);
        GripperFingerR2->SetSimulatePhysics(true);

        // ======================== Constraints ========================

        ArmTool_GripperLink->ComponentName1.ComponentName = TEXT("ArmTool");
        ArmTool_GripperLink->ComponentName2.ComponentName = TEXT("GripperLink");
        ArmTool_GripperLink->SetRelativeLocation(FVector(0, 0, 0));
        ArmTool_GripperLink->SetRelativeRotation(FRotator(0,180,180));
        ArmTool_GripperLink->SetAngularSwing1Limit(ACM_Locked, 0);
        ArmTool_GripperLink->SetAngularSwing2Limit(ACM_Locked, 0);
        ArmTool_GripperLink->SetAngularTwistLimit(ACM_Locked, 0);
        ArmTool_GripperLink->SetLinearXLimit(LCM_Locked, 0);
        ArmTool_GripperLink->SetLinearYLimit(LCM_Locked, 0);
        ArmTool_GripperLink->SetLinearZLimit(LCM_Locked, 0);

        GripperLink->SetupAttachment(ArmTool_GripperLink);
        ArmTool_GripperLink->SetupAttachment(ArmTool);

        GripperFingerMountL_GripperFingerL1->ComponentName1.ComponentName = TEXT("GripperFingerMountL");
        GripperFingerMountL_GripperFingerL1->ComponentName2.ComponentName = TEXT("GripperFingerL1");
        GripperFingerMountL_GripperFingerL1->SetRelativeLocation(FVector(0, 1, 0.4));
        GripperFingerMountL_GripperFingerL1->SetRelativeRotation(FRotator(0, 1.57, 0));
        GripperFingerMountL_GripperFingerL1->SetAngularSwing1Limit(ACM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetAngularSwing2Limit(ACM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetAngularTwistLimit(ACM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetLinearXLimit(LCM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetLinearYLimit(LCM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetLinearZLimit(LCM_Locked, 0);

        GripperFingerL1->SetupAttachment(GripperFingerMountL_GripperFingerL1);
        GripperFingerMountL_GripperFingerL1->SetupAttachment(GripperFingerMountL);

        GripperFingerMountR_GripperFingerR1->ComponentName1.ComponentName = TEXT("GripperFingerMountR");
        GripperFingerMountR_GripperFingerR1->ComponentName2.ComponentName = TEXT("GripperFingerR1");
        GripperFingerMountR_GripperFingerR1->SetRelativeLocation(FVector(2.25, 1, 0.4));
        GripperFingerMountR_GripperFingerR1->SetRelativeRotation(FRotator(0, 1.57, 0));
        GripperFingerMountR_GripperFingerR1->SetAngularSwing1Limit(ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetAngularSwing2Limit(ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetAngularTwistLimit(ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetLinearXLimit(LCM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetLinearYLimit(LCM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetLinearZLimit(LCM_Locked, 0);

        GripperFingerR1->SetupAttachment(GripperFingerMountR_GripperFingerR1);
        GripperFingerMountR_GripperFingerR1->SetupAttachment(GripperFingerMountR);

        GripperFingerMountR_GripperFingerR2->ComponentName1.ComponentName = TEXT("GripperFingerMountR");
        GripperFingerMountR_GripperFingerR2->ComponentName2.ComponentName = TEXT("GripperFingerR2");
        GripperFingerMountR_GripperFingerR2->SetRelativeLocation(FVector(-2.25, 1, 0.4));
        GripperFingerMountR_GripperFingerR2->SetRelativeRotation(FRotator(0, 1.57, 0));
        GripperFingerMountR_GripperFingerR2->SetAngularSwing1Limit(ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetAngularSwing2Limit(ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetAngularTwistLimit(ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetLinearXLimit(LCM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetLinearYLimit(LCM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetLinearZLimit(LCM_Locked, 0);

        GripperFingerR2->SetupAttachment(GripperFingerMountR_GripperFingerR2);
        GripperFingerMountR_GripperFingerR2->SetupAttachment(GripperFingerMountR);

        // ====================== Joints ==============================

        AddJoint(TEXT("gripper_link"), TEXT("gripper_left_finger_link"), TEXT("gripper_finger_joint"), GripperLink_GripperLeftFingerLink);
        AddJoint(TEXT("gripper_link"), TEXT("gripper_right_finger_link"), TEXT("gripper_right_finger_joint"), GripperLink_GripperRightFingerLink);
        AddJoint(TEXT("gripper_left_finger_link"), TEXT("gripper_finger_mount_l"), TEXT("gripper_finger_mount_l_joint"), GripperLeftFingerLink_GripperFingerMountL);
        AddJoint(TEXT("gripper_right_finger_link"), TEXT("gripper_finger_mount_r"), TEXT("gripper_finger_mount_r_joint"), GripperRightFingerLink_GripperFingerMountR);

        GripperLink_GripperLeftFingerLink->SetRelativeLocation(FVector(-3.4, 0,0));
        GripperLink_GripperLeftFingerLink->SetRelativeRotation(FRotator(0,0,0));
        GripperLink_GripperLeftFingerLink->LinearDOF = 1;
        GripperLink_GripperLeftFingerLink->RotationalDOF = 0;
        GripperLink_GripperLeftFingerLink->LinearForceLimit = MaxForce;
        GripperLink_GripperLeftFingerLink->LinearSpring = GripperLinearSpring;
        GripperLink_GripperLeftFingerLink->LinearDamper = GripperLinearDamper;
        GripperLink_GripperLeftFingerLink->LinearVelMax = FVector(1000, 0, 0);

        GripperLeftFingerLink->SetupAttachment(GripperLink_GripperLeftFingerLink);
        GripperLeftFingerLink->SetRelativeLocation(FVector(0,0,0));
        GripperLeftFingerLink->SetRelativeRotation(FRotator(0,0,0));

        GripperLink_GripperRightFingerLink->SetRelativeLocation(FVector(3.4, 0, 0));
        GripperLink_GripperRightFingerLink->SetRelativeRotation(FRotator(0,0,0));
        GripperLink_GripperRightFingerLink->LinearDOF = 1;
        GripperLink_GripperRightFingerLink->RotationalDOF = 0;
        GripperLink_GripperRightFingerLink->LinearForceLimit = MaxForce;
        GripperLink_GripperRightFingerLink->LinearSpring = GripperLinearSpring;
        GripperLink_GripperRightFingerLink->LinearDamper = GripperLinearDamper;
        GripperLink_GripperRightFingerLink->LinearVelMax = FVector(1000,0,0);

        GripperRightFingerLink->SetupAttachment(GripperLink_GripperRightFingerLink);
        GripperRightFingerLink->SetRelativeLocation(FVector(0,0,0));
        GripperRightFingerLink->SetRelativeRotation(FRotator(0,0,0));

        GripperLeftFingerLink_GripperFingerMountL->SetRelativeLocation(FVector(5, 0, -16.5));
        GripperLeftFingerLink_GripperFingerMountL->SetRelativeRotation(FRotator(0,0,0));
        GripperLeftFingerLink_GripperFingerMountL->LinearDOF = 0;
        GripperLeftFingerLink_GripperFingerMountL->RotationalDOF = 1;
        GripperLeftFingerLink_GripperFingerMountL->AngularForceLimit = MaxForce;
        GripperLeftFingerLink_GripperFingerMountL->AngularSpring = GripperAngularSpring;
        GripperLeftFingerLink_GripperFingerMountL->AngularDamper = GripperAngularDamper;
        GripperLeftFingerLink_GripperFingerMountL->AngularVelMax = FVector(3600, 0,0);

        GripperFingerMountL->SetupAttachment(GripperLeftFingerLink_GripperFingerMountL);
        GripperFingerMountL->SetRelativeLocation(FVector(0,0,0));
        GripperFingerMountL->SetRelativeRotation(FRotator(0,0,0));

        GripperRightFingerLink_GripperFingerMountR->SetRelativeLocation(FVector(-5, 0, -16.5));
        GripperRightFingerLink_GripperFingerMountR->SetRelativeRotation(FRotator(0,0,0));
        GripperRightFingerLink_GripperFingerMountR->LinearDOF = 0;
        GripperRightFingerLink_GripperFingerMountR->RotationalDOF = 1;
        GripperRightFingerLink_GripperFingerMountR->AngularForceLimit = MaxForce;
        GripperRightFingerLink_GripperFingerMountR->AngularSpring = GripperAngularSpring;
        GripperRightFingerLink_GripperFingerMountR->AngularDamper = GripperAngularDamper;
        GripperRightFingerLink_GripperFingerMountR->AngularVelMax = FVector(3600, 0, 0);

        GripperFingerMountR->SetupAttachment(GripperRightFingerLink_GripperFingerMountR);
        GripperFingerMountR->SetRelativeLocation(FVector(0,0,0));
        GripperFingerMountR->SetRelativeRotation(FRotator(0,0,0));
        
        return true;
    }
    return false;
}


