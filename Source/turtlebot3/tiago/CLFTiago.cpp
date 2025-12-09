#include "CLFTiago.h"


ACLFTiago::ACLFTiago(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    VehicleMoveComponentClass = URRDifferentialDriveComponent::StaticClass();
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ACLFTiago::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }

    //Add links
    AddLink(TEXT("base_link"), Base);
    AddLink(TEXT("wheel_left_link"), WheelLeft);
    AddLink(TEXT("wheel_right_link"), WheelRight);
    AddLink(TEXT("torso_lift_link"), TorsoLiftWithArm);
    AddLink(TEXT("head_1_link"), HeadBase);
    AddLink(TEXT("head_2_link"), HeadTop);
    AddLink(TEXT("arm_1_link"), Arm1);
    AddLink(TEXT("arm_2_link"), Arm2);
    AddLink(TEXT("arm_3_link"), Arm3);
    AddLink(TEXT("arm_4_link"), Arm4);
    AddLink(TEXT("arm_5_link"), Arm5);
    AddLink(TEXT("arm_6_link"), Arm6);
    AddLink(TEXT("gripper_link"), GripperLink);
    AddLink(TEXT("gripper_left_finger_link"), GripperLeftFingerLink);
    AddLink(TEXT("gripper_right_finger_link"), GripperRightFingerLink);
    AddLink(TEXT("gripper_finger_mount_l_link"), GripperFingerMountL);
    AddLink(TEXT("gripper_finger_mount_r_link"), GripperFingerMountR);
    AddLink(TEXT("caster_back_left_1_link"), CasterBase1);
    AddLink(TEXT("caster_back_left_2_link"), CasterRoll1);
    AddLink(TEXT("caster_back_right_1_link"), CasterBase2);
    AddLink(TEXT("caster_back_right_2_link"), CasterRoll2);
    AddLink(TEXT("caster_front_left_1_link"), CasterBase3);
    AddLink(TEXT("caster_front_left_2_link"), CasterRoll3);
    AddLink(TEXT("caster_front_right_1_link"), CasterBase4);
    AddLink(TEXT("caster_front_right_2_link"), CasterRoll4);
    
    //Constraints
    Base_WheelLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_WheelLeft"));
    Base_WheelLeft->SetupAttachment(Base);

    Base_WheelRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_WheelRight"));
    Base_WheelRight->SetupAttachment(Base);

    Base_TorsoLift = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_TorsoLift"));
    Base_TorsoLift->SetupAttachment(Base);

    Base_CasterBase1 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_Caster1Base"));
    Base_CasterBase1->SetupAttachment(Base);

    Base_CasterBase2 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_Caster2Base"));
    Base_CasterBase2->SetupAttachment(Base);

    Base_CasterBase3 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_Caster3Base"));
    Base_CasterBase3->SetupAttachment(Base);

    Base_CasterBase4 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_Caster4Base"));
    Base_CasterBase4->SetupAttachment(Base);

    CasterBase1_CasterRoll1 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Caster1Base_Caster1Roll"));
    CasterBase1_CasterRoll1->SetupAttachment(CasterBase1);

    CasterBase2_CasterRoll2 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Caster2Base_Caster2Roll"));
    CasterBase2_CasterRoll2->SetupAttachment(CasterBase2);

    CasterBase3_CasterRoll3 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Caster3Base_Caster3Roll"));
    CasterBase3_CasterRoll3->SetupAttachment(CasterBase3);

    CasterBase4_CasterRoll4 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Caster4Base_Caster4Roll"));
    CasterBase4_CasterRoll4->SetupAttachment(CasterBase4);

    TorsoLift_HeadBase = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("TorsoLift_HeadBase"));
    TorsoLift_HeadBase->SetupAttachment(TorsoLiftWithArm);

    HeadBase_HeadTop = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("HeadBase_HeadTop"));
    HeadBase_HeadTop->SetupAttachment(HeadBase);

    TorsoLift_Arm1 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("TorsoLift_Arm1"));
    TorsoLift_Arm1->SetupAttachment(TorsoLiftWithArm);

    Arm1_Arm2 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Arm1_Arm2"));
    Arm1_Arm2->SetupAttachment(Arm1);

    Arm2_Arm3 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Arm2_Arm3"));
    Arm2_Arm3->SetupAttachment(Arm2);

    Arm3_Arm4 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Arm3_Arm4"));
    Arm3_Arm4->SetupAttachment(Arm3);

    Arm4_Arm5 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Arm4_Arm5"));
    Arm4_Arm5->SetupAttachment(Arm4);

    Arm5_Arm6 = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Arm5_Arm6"));
    Arm5_Arm6->SetupAttachment(Arm5);

    Arm6_GripperLink = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Arm6_GripperLink"));
    Arm6_GripperLink->SetupAttachment(Arm6);

    GripperLink_GripperLeftFingerLink = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("GripperLink_GripperLeftFingerLink"));
    GripperLink_GripperLeftFingerLink->SetupAttachment(GripperLink);

    GripperLink_GripperRightFingerLink = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("GripperLink_GripperRightFingerLink"));
    GripperLink_GripperRightFingerLink->SetupAttachment(GripperLink);

    GripperLeftFingerLink_GripperFingerMountL = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("GripperLeftFingerLink_GripperFingerMountL"));
    GripperLeftFingerLink_GripperFingerMountL->SetupAttachment(GripperLeftFingerLink);

    GripperRightFingerLink_GripperFingerMountR = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("GripperRightFingerLink_GripperFingerMountR"));
    GripperRightFingerLink_GripperFingerMountR->SetupAttachment(GripperRightFingerLink);

    GripperFingerMountL_GripperFingerL1 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("GripperFingerMountL_GripperFingerL1"));
    GripperFingerMountR_GripperFingerR1 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("GripperFingerMountR_GripperFingerR1"));
    GripperFingerMountR_GripperFingerR2 = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("GripperFingerMountR_GripperFingerR2"));

    bBodyComponentsCreated = true;

    return true;
}

void ACLFTiago::SetupWheelDrives()
{
    if (bBodyComponentsCreated && IsValid(MovementComponent))
    {
        URRDifferentialDriveComponent* diffDriveComponent = CastChecked<URRDifferentialDriveComponent>(MovementComponent);
        diffDriveComponent->SetWheels(Base_WheelLeft, Base_WheelRight);
        diffDriveComponent->WheelRadius = WheelRadius;
        diffDriveComponent->WheelSeparationHalf = WheelSeparationHalf;
        diffDriveComponent->SetPerimeter();
    }
}

bool ACLFTiago::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        //Add Joints
        AddJoint(TEXT("base_link"), TEXT("wheel_right_link"), TEXT("wheel_right_joint"), Base_WheelRight);
        AddJoint(TEXT("base_link"), TEXT("wheel_left_link"), TEXT("wheel_left_joint"), Base_WheelLeft);
        AddJoint(TEXT("base_link"), TEXT("torso_lift_link"), TEXT("torso_lift_joint"), Base_TorsoLift);
        AddJoint(TEXT("torso_lift_link"), TEXT("head_1_link"), TEXT("head_1_joint"), TorsoLift_HeadBase);
        AddJoint(TEXT("head_1_link"), TEXT("head_2_link"), TEXT("head_2_joint"), HeadBase_HeadTop);
        AddJoint(TEXT("torso_lift_link"), TEXT("arm_1_link"), TEXT("arm_1_joint"), TorsoLift_Arm1);
        AddJoint(TEXT("arm_1_link"), TEXT("arm_2_link"), TEXT("arm_2_joint"), Arm1_Arm2);
        AddJoint(TEXT("arm_2_link"), TEXT("arm_3_link"), TEXT("arm_3_joint"), Arm2_Arm3);
        AddJoint(TEXT("arm_3_link"), TEXT("arm_4_link"), TEXT("arm_4_joint"), Arm3_Arm4);
        AddJoint(TEXT("arm_4_link"), TEXT("arm_5_link"), TEXT("arm_5_joint"), Arm4_Arm5);
        AddJoint(TEXT("arm_5_link"), TEXT("arm_6_link"), TEXT("arm_6_joint"), Arm5_Arm6);
        AddJoint(TEXT("arm_6_link"), TEXT("gripper_link"), TEXT("arm_7_joint"), Arm6_GripperLink);
        AddJoint(TEXT("gripper_link"), TEXT("gripper_left_finger_link"), TEXT("gripper_finger_joint"), GripperLink_GripperLeftFingerLink);
        AddJoint(TEXT("gripper_link"), TEXT("gripper_right_finger_link"), TEXT("gripper_right_finger_joint"), GripperLink_GripperRightFingerLink);
        AddJoint(TEXT("gripper_left_finger_link"), TEXT("gripper_finger_mount_l_link"), TEXT("gripper_finger_mount_l_joint"), GripperLeftFingerLink_GripperFingerMountL);
        AddJoint(TEXT("gripper_right_finger_link"), TEXT("gripper_finger_mount_r_link"), TEXT("gripper_finger_mount_r_joint"), GripperRightFingerLink_GripperFingerMountR);
        AddJoint(TEXT("base_link"), TEXT("caster_back_left_1_link"), TEXT("caster_back_left_1_joint"), Base_CasterBase1);
        AddJoint(TEXT("base_link"), TEXT("caster_back_right_1_link"), TEXT("caster_back_right_1_joint"), Base_CasterBase2);
        AddJoint(TEXT("base_link"), TEXT("caster_front_left_1_link"), TEXT("caster_front_left_1_joint"), Base_CasterBase3);
        AddJoint(TEXT("base_link"), TEXT("caster_front_right_1_link"), TEXT("caster_front_right_1_joint"), Base_CasterBase4);
        AddJoint(TEXT("caster_back_left_1_link"), TEXT("caster_back_left_2_link"), TEXT("caster_back_left_2_joint"), CasterBase1_CasterRoll1);
        AddJoint(TEXT("caster_back_right_1_link"), TEXT("caster_back_right_2_link"), TEXT("caster_back_right_2_joint"), CasterBase2_CasterRoll2);
        AddJoint(TEXT("caster_front_left_1_link"), TEXT("caster_front_left_2_link"), TEXT("caster_front_left_2_joint"), CasterBase3_CasterRoll3);
        AddJoint(TEXT("caster_front_right_1_link"), TEXT("caster_front_right_2_link"), TEXT("caster_front_right_2_joint"), CasterBase4_CasterRoll4);
        
        WheelLeft->SetupAttachment(Base_WheelLeft);
        WheelLeft->SetRelativeLocation(FVector(0, 0, 0));
        WheelLeft->SetRelativeRotation(FRotator(0, 90, 0));
        WheelRight->SetupAttachment(Base_WheelRight);
        WheelRight->SetRelativeLocation(FVector(0, 0, 0));
        WheelRight->SetRelativeRotation(FRotator(0, -90, 0));

        // set joint parameters TODO: Fix relative rotations!!!
        Base_WheelLeft->SetRelativeLocation(FVector(0, -20.22, 0));
        Base_WheelLeft->SetRelativeRotation(FRotator(0, -90, 0));
        Base_WheelLeft->LinearDOF = 0;
        Base_WheelLeft->RotationalDOF = 1;
        Base_WheelLeft->AngularForceLimit = MaxForce;
        Base_WheelLeft->AngularVelMax = FVector(3600, 0, 0);

        Base_WheelRight->SetRelativeLocation(FVector(0, 20.22, 0));
        Base_WheelRight->SetRelativeRotation(FRotator(0, 90, 0));
        Base_WheelRight->LinearDOF = 0;
        Base_WheelRight->RotationalDOF = 1;
        Base_WheelRight->AngularForceLimit = MaxForce;
        Base_WheelRight->AngularVelMax = FVector(3600, 0, 0);

        //Caster
        //Back Left
        Base_CasterBase1->SetRelativeLocation(FVector(-17.35,10.2,-3.35));
        Base_CasterBase1->SetRelativeRotation(FRotator(90,0,0));
        Base_CasterBase1->LinearDOF = 0;
        Base_CasterBase1->RotationalDOF = 1;
        Base_CasterBase1->AngularForceLimit = MaxForce;
        Base_CasterBase1->AngularVelMax = FVector(3600, 0,0);

        CasterBase1->SetupAttachment(Base_CasterBase1);
        CasterBase1->SetRelativeLocation(FVector(0,0,0));
        CasterBase1->SetRelativeRotation(FRotator(0,0,0));

        CasterBase1_CasterRoll1->SetRelativeLocation(FVector(-4, 0, 1.6));
        CasterBase1_CasterRoll1->SetRelativeRotation(FRotator(0,-90,0));
        CasterBase1_CasterRoll1->LinearDOF = 0;
        CasterBase1_CasterRoll1->RotationalDOF = 1;
        CasterBase1_CasterRoll1->AngularForceLimit = MaxForce;
        CasterBase1_CasterRoll1->AngularVelMax = FVector(3600, 0, 0);

        CasterRoll1->SetupAttachment(CasterBase1_CasterRoll1);
        CasterRoll1->SetRelativeLocation(FVector(0,0,0));
        CasterRoll1->SetRelativeRotation(FRotator(0,0,0));

        //Back Right
        Base_CasterBase2->SetRelativeLocation(FVector(-17.35,-10.2,-3.35));
        Base_CasterBase2->SetRelativeRotation(FRotator(90,0,0));
        Base_CasterBase2->LinearDOF = 0;
        Base_CasterBase2->RotationalDOF = 1;
        Base_CasterBase2->AngularForceLimit = MaxForce;
        Base_CasterBase2->AngularVelMax = FVector(3600, 0,0);

        CasterBase2->SetupAttachment(Base_CasterBase2);
        CasterBase2->SetRelativeLocation(FVector(0,0,0));
        CasterBase2->SetRelativeRotation(FRotator(0,0,0));

        CasterBase2_CasterRoll2->SetRelativeLocation(FVector(-4, 0, 1.6));
        CasterBase2_CasterRoll2->SetRelativeRotation(FRotator(0,-90,0));
        CasterBase2_CasterRoll2->LinearDOF = 0;
        CasterBase2_CasterRoll2->RotationalDOF = 1;
        CasterBase2_CasterRoll2->AngularForceLimit = MaxForce;
        CasterBase2_CasterRoll2->AngularVelMax = FVector(3600, 0, 0);

        CasterRoll2->SetupAttachment(CasterBase2_CasterRoll2);
        CasterRoll2->SetRelativeLocation(FVector(0,0,0));
        CasterRoll2->SetRelativeRotation(FRotator(0,0,0));

        //Front Left
        Base_CasterBase3->SetRelativeLocation(FVector(16.95,10.2,-3.35));
        Base_CasterBase3->SetRelativeRotation(FRotator(90,0,0));
        Base_CasterBase3->LinearDOF = 0;
        Base_CasterBase3->RotationalDOF = 1;
        Base_CasterBase3->AngularForceLimit = MaxForce;
        Base_CasterBase3->AngularVelMax = FVector(3600, 0,0);

        CasterBase3->SetupAttachment(Base_CasterBase3);
        CasterBase3->SetRelativeLocation(FVector(0,0,0));
        CasterBase3->SetRelativeRotation(FRotator(0,0,0));

        CasterBase3_CasterRoll3->SetRelativeLocation(FVector(-4, 0, 1.6));
        CasterBase3_CasterRoll3->SetRelativeRotation(FRotator(0,-90,0));
        CasterBase3_CasterRoll3->LinearDOF = 0;
        CasterBase3_CasterRoll3->RotationalDOF = 1;
        CasterBase3_CasterRoll3->AngularForceLimit = MaxForce;
        CasterBase3_CasterRoll3->AngularVelMax = FVector(3600, 0, 0);

        CasterRoll3->SetupAttachment(CasterBase3_CasterRoll3);
        CasterRoll3->SetRelativeLocation(FVector(0,0,0));
        CasterRoll3->SetRelativeRotation(FRotator(0,0,0));

        //Front Right
        Base_CasterBase4->SetRelativeLocation(FVector(16.95,-10.2,-3.35));
        Base_CasterBase4->SetRelativeRotation(FRotator(90,0,0));
        Base_CasterBase4->LinearDOF = 0;
        Base_CasterBase4->RotationalDOF = 1;
        Base_CasterBase4->AngularForceLimit = MaxForce;
        Base_CasterBase4->AngularVelMax = FVector(3600, 0,0);

        CasterBase4->SetupAttachment(Base_CasterBase4);
        CasterBase4->SetRelativeLocation(FVector(0,0,0));
        CasterBase4->SetRelativeRotation(FRotator(0,0,0));

        CasterBase4_CasterRoll4->SetRelativeLocation(FVector(-4, 0, 1.6));
        CasterBase4_CasterRoll4->SetRelativeRotation(FRotator(0,-90,0));
        CasterBase4_CasterRoll4->LinearDOF = 0;
        CasterBase4_CasterRoll4->RotationalDOF = 1;
        CasterBase4_CasterRoll4->AngularForceLimit = MaxForce;
        CasterBase4_CasterRoll4->AngularVelMax = FVector(3600, 0, 0);

        CasterRoll4->SetupAttachment(CasterBase4_CasterRoll4);
        CasterRoll4->SetRelativeLocation(FVector(0,0,0));
        CasterRoll4->SetRelativeRotation(FRotator(0,0,0));

        Base_TorsoLift->SetRelativeLocation(FVector(-6.2, 0, 88.85));
        Base_TorsoLift->SetRelativeRotation(FRotator(0,0,0));
        Base_TorsoLift->LinearDOF = 1;
        Base_TorsoLift->RotationalDOF = 0;
        //Base_TorsoLift->PositionMax = FVector(0, 0, 35.0);
        //Base_TorsoLift->PositionMin = FVector(0, 0,0);
        //Base_TorsoLift->AngularVelMax = FVector(0, 0,0);

        TorsoLiftWithArm->SetupAttachment(Base_TorsoLift);
        TorsoLiftWithArm->SetRelativeLocation(FVector(0,0,0));
        TorsoLiftWithArm->SetRelativeRotation(FRotator(0, 0, 0));

        TorsoLift_HeadBase->SetRelativeLocation(FVector(18.2, 0, 0));
        TorsoLift_HeadBase->SetRelativeRotation(FRotator(0, 0, 0));
        TorsoLift_HeadBase->LinearDOF = 0;
        TorsoLift_HeadBase->RotationalDOF = 1;
        TorsoLift_HeadBase->AngularForceLimit = MaxForce;
        TorsoLift_HeadBase->AngularVelMax = FVector(0, 0, 3600);

        HeadBase->SetupAttachment(TorsoLift_HeadBase);
        HeadBase->SetRelativeLocation(FVector(0,0,0));
        HeadBase->SetRelativeRotation(FRotator(0, 0, 0));

        HeadBase_HeadTop->SetRelativeLocation(FVector(0.5, 0, 9.8));
        HeadBase_HeadTop->SetRelativeRotation(FRotator(0, 0, 0));
        HeadBase_HeadTop->LinearDOF = 0;
        HeadBase_HeadTop->RotationalDOF = 1;
        HeadBase_HeadTop->AngularForceLimit = MaxForce;
        HeadBase_HeadTop->AngularVelMax = FVector(0, 3600, 0);

        HeadTop->SetupAttachment(HeadBase_HeadTop);
        HeadTop->SetRelativeLocation(FVector(0,0,0));
        HeadTop->SetRelativeRotation(FRotator(0, 0, 0));

        TorsoLift_Arm1->SetRelativeLocation(FVector(15.505, 1.4, -15.1));
        TorsoLift_Arm1->SetRelativeRotation(FRotator(0,0,0));
        TorsoLift_Arm1->LinearDOF = 0;
        TorsoLift_Arm1->RotationalDOF = 1;
        TorsoLift_Arm1->AngularForceLimit = MaxForce;
        TorsoLift_Arm1->AngularVelMax = FVector(0, 0, 3600);

        Arm1->SetupAttachment(TorsoLift_Arm1);
        Arm1->SetRelativeLocation(FVector(0,0,0));
        Arm1->SetRelativeRotation(FRotator(0,0,0));

        Arm1_Arm2->SetRelativeLocation(FVector(12.5, 1.95, -3.1));
        Arm1_Arm2->SetRelativeRotation(FRotator(0,0,0));
        Arm1_Arm2->LinearDOF = 0;
        Arm1_Arm2->RotationalDOF = 1;
        Arm1_Arm2->AngularForceLimit = MaxForce;
        Arm1_Arm2->AngularVelMax = FVector(0, 0, 3600);

        Arm2->SetupAttachment(Arm1_Arm2);
        Arm2->SetRelativeLocation(FVector(0,0,0));
        Arm2->SetRelativeRotation(FRotator(0,0,0));

        Arm2_Arm3->SetRelativeLocation(FVector(8.9, 0, -0.15));
        Arm2_Arm3->SetRelativeRotation(FRotator(0,0,0));
        Arm2_Arm3->LinearDOF = 0;
        Arm2_Arm3->RotationalDOF = 1;
        Arm2_Arm3->AngularForceLimit = MaxForce;
        Arm2_Arm3->AngularVelMax = FVector(0, 0, 3600);

        Arm3->SetupAttachment(Arm2_Arm3);
        Arm3->SetRelativeLocation(FVector(0,0,0));
        Arm3->SetRelativeRotation(FRotator(0,0,0));

        Arm3_Arm4->SetRelativeLocation(FVector(-2, 2.7, -22.2));
        Arm3_Arm4->SetRelativeRotation(FRotator(0,0,0));
        Arm3_Arm4->LinearDOF = 0;
        Arm3_Arm4->RotationalDOF = 1;
        Arm3_Arm4->AngularForceLimit = MaxForce;
        Arm3_Arm4->AngularVelMax = FVector(0, 0, 3600);

        Arm4->SetupAttachment(Arm3_Arm4);
        Arm4->SetRelativeLocation(FVector(0,0,0));
        Arm4->SetRelativeRotation(FRotator(0,0,0));

        Arm4_Arm5->SetRelativeLocation(FVector(-16.2, 2, 2.7));
        Arm4_Arm5->SetRelativeRotation(FRotator(0,0,0));
        Arm4_Arm5->LinearDOF = 0;
        Arm4_Arm5->RotationalDOF = 1;
        Arm4_Arm5->AngularForceLimit = MaxForce;
        Arm4_Arm5->AngularVelMax = FVector(0, 0, 3600);

        Arm5->SetupAttachment(Arm4_Arm5);
        Arm5->SetRelativeLocation(FVector(0,0,0));
        Arm5->SetRelativeRotation(FRotator(0,0,0));

        Arm5_Arm6->SetRelativeLocation(FVector(0, 0, 15));
        Arm5_Arm6->SetRelativeRotation(FRotator(0,0,0));
        Arm5_Arm6->LinearDOF = 0;
        Arm5_Arm6->RotationalDOF = 1;
        Arm5_Arm6->AngularForceLimit = MaxForce;
        Arm5_Arm6->AngularVelMax = FVector(0, 0, 3600);

        Arm6->SetupAttachment(Arm5_Arm6);
        Arm6->SetRelativeLocation(FVector(0,0,0));
        Arm6->SetRelativeRotation(FRotator(0,0,0));

        //Gripper
        Arm6_GripperLink->SetRelativeLocation(FVector(1,0,0));
        Arm6_GripperLink->SetRelativeRotation(FRotator(0,0,0));
        Arm6_GripperLink->LinearDOF = 0;
        Arm6_GripperLink->RotationalDOF = 1;
        Arm6_GripperLink->AngularForceLimit = MaxForce;
        Arm6_GripperLink->AngularVelMax = FVector(3600,0,0);

        GripperLink->SetupAttachment(Arm6_GripperLink);
        GripperLink->SetRelativeLocation(FVector(0,0,0));
        GripperLink->SetRelativeRotation(FRotator(0,0,0));

        GripperLink_GripperLeftFingerLink->SetRelativeLocation(FVector(-3.4,0,0));
        GripperLink_GripperLeftFingerLink->SetRelativeRotation(FRotator(0,0,0));
        GripperLink_GripperLeftFingerLink->LinearDOF = 1;
        GripperLink_GripperLeftFingerLink->RotationalDOF = 0;
        GripperLink_GripperLeftFingerLink->LinearForceLimit = MaxForce;
        GripperLink_GripperLeftFingerLink->LinearVelMax = FVector(10000, 0,0);

        GripperLeftFingerLink->SetupAttachment(GripperLink_GripperLeftFingerLink);
        GripperLeftFingerLink->SetRelativeLocation(FVector(0,0,0));
        GripperLeftFingerLink->SetRelativeRotation(FRotator(0,0,0));

        GripperLink_GripperRightFingerLink->SetRelativeLocation(FVector(3.4,0,0));
        GripperLink_GripperRightFingerLink->SetRelativeRotation(FRotator(0,0,0));
        GripperLink_GripperRightFingerLink->LinearDOF = 1;
        GripperLink_GripperRightFingerLink->RotationalDOF = 0;
        GripperLink_GripperRightFingerLink->LinearForceLimit = MaxForce;
        GripperLink_GripperRightFingerLink->LinearVelMax = FVector(10000,0,0);

        GripperRightFingerLink->SetupAttachment(GripperLink_GripperRightFingerLink);
        GripperRightFingerLink->SetRelativeLocation(FVector(0,0,0));
        GripperRightFingerLink->SetRelativeRotation(FRotator(0,0,0));

        GripperLeftFingerLink_GripperFingerMountL->SetRelativeLocation(FVector(5,0,-16.5));
        GripperLeftFingerLink_GripperFingerMountL->SetRelativeRotation(FRotator(0,0,0));
        GripperLeftFingerLink_GripperFingerMountL->LinearDOF = 0;
        GripperLeftFingerLink_GripperFingerMountL->RotationalDOF = 1;
        GripperLeftFingerLink_GripperFingerMountL->AngularForceLimit = MaxForce;
        GripperLeftFingerLink_GripperFingerMountL->AngularVelMax = FVector(3600,0,0);

        GripperFingerMountL->SetupAttachment(GripperLeftFingerLink_GripperFingerMountL);
        GripperFingerMountL->SetRelativeLocation(FVector(0,0,0));
        GripperFingerMountL->SetRelativeRotation(FRotator(0,0,0));

        GripperRightFingerLink_GripperFingerMountR->SetRelativeLocation(FVector(-5,0,-16.5));
        GripperRightFingerLink_GripperFingerMountR->SetRelativeRotation(FRotator(0,0,0));
        GripperRightFingerLink_GripperFingerMountR->LinearDOF = 0;
        GripperRightFingerLink_GripperFingerMountR->RotationalDOF = 1;
        GripperRightFingerLink_GripperFingerMountR->AngularForceLimit = MaxForce;
        GripperRightFingerLink_GripperFingerMountR->AngularVelMax = FVector(3600,0,0);

        GripperFingerMountR->SetupAttachment(GripperRightFingerLink_GripperFingerMountR);
        GripperFingerMountR->SetRelativeLocation(FVector(0,0,0));
        GripperFingerMountR->SetRelativeRotation(FRotator(0,0,0));


        // Finger
        GripperFingerMountL_GripperFingerL1->ComponentName1.ComponentName = TEXT("GripperFingerMountL");
        GripperFingerMountL_GripperFingerL1->ComponentName2.ComponentName = TEXT("GripperFingerL1");
        GripperFingerMountL_GripperFingerL1->SetRelativeLocation(FVector(0,1,0.4));
        GripperFingerMountL_GripperFingerL1->SetDisableCollision(true);
        GripperFingerMountL_GripperFingerL1->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        GripperFingerMountL_GripperFingerL1->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        GripperFingerL1->SetupAttachment(GripperFingerMountL_GripperFingerL1);

        GripperFingerMountL_GripperFingerL1->SetupAttachment(GripperFingerMountL);

        GripperFingerMountR_GripperFingerR1->ComponentName1.ComponentName = TEXT("GripperFingerMountR");
        GripperFingerMountR_GripperFingerR1->ComponentName2.ComponentName = TEXT("GripperFingerR1");
        GripperFingerMountR_GripperFingerR1->SetRelativeLocation(FVector(2.25, 1, 0.4));
        GripperFingerMountR_GripperFingerR1->SetDisableCollision(true);
        GripperFingerMountR_GripperFingerR1->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        GripperFingerMountR_GripperFingerR1->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        GripperFingerR1->SetupAttachment(GripperFingerMountR_GripperFingerR1);

        GripperFingerMountR_GripperFingerR1->SetupAttachment(GripperFingerMountR);

        GripperFingerMountR_GripperFingerR2->ComponentName1.ComponentName = TEXT("GripperFingerMountR");
        GripperFingerMountR_GripperFingerR2->ComponentName2.ComponentName = TEXT("GripperFingerR2");
        GripperFingerMountR_GripperFingerR2->SetRelativeLocation(FVector(-2.25, 1, 0.4));
        GripperFingerMountR_GripperFingerR2->SetDisableCollision(true);
        GripperFingerMountR_GripperFingerR2->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        GripperFingerMountR_GripperFingerR2->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        GripperFingerR2->SetupAttachment(GripperFingerMountR_GripperFingerR2);

        GripperFingerMountR_GripperFingerR2->SetupAttachment(GripperFingerMountR); 
        
        return true;
    }
    else
    {
        return false;
    }
}

