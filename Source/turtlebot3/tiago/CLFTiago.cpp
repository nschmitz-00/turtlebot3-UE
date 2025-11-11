#include "CLFTiago.h"

#include "NavigationSystemTypes.h"

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
    
    //Constraints
    Base_WheelLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_WheelLeft"));
    Base_WheelLeft->SetupAttachment(Base);

    Base_WheelRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_WheelRight"));
    Base_WheelRight->SetupAttachment(Base);

    Base_TorsoLift = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_TorsoLift"));
    Base_TorsoLift->SetupAttachment(Base);

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

        WheelLeft->SetupAttachment(Base_WheelLeft);
        WheelLeft->SetRelativeLocation(FVector(0, 0, 0));
        WheelLeft->SetRelativeRotation(FRotator(0, 90, 0));
        WheelRight->SetupAttachment(Base_WheelRight);
        WheelRight->SetRelativeLocation(FVector(0, 0, 0));
        WheelRight->SetRelativeRotation(FRotator(0, -90, 0));

        // set joint parameters
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

        TorsoLiftWithArm->SetupAttachment(Base_TorsoLift);
        TorsoLiftWithArm->SetRelativeLocation(FVector(0,0,0));
        TorsoLiftWithArm->SetRelativeRotation(FRotator(0, 0, 0));

        Base_TorsoLift->SetRelativeLocation(FVector(-6.2, 0, 88.85));
        Base_TorsoLift->SetRelativeRotation(FRotator(0,0,0));
        Base_TorsoLift->LinearDOF = 3;
        Base_TorsoLift->RotationalDOF = 3;
        //Base_TorsoLift->PositionMax = FVector(0, 0, 35.0);
        //Base_TorsoLift->PositionMin = FVector(0, 0,0);
        //Base_TorsoLift->AngularVelMax = FVector(0, 0,0);

        TorsoLift_HeadBase->SetRelativeLocation(FVector(18.2, 0, 0));
        TorsoLift_HeadBase->SetRelativeRotation(FRotator(0, 0, 0));
        TorsoLift_HeadBase->LinearDOF = 0;
        TorsoLift_HeadBase->RotationalDOF = 2;
        TorsoLift_HeadBase->AngularForceLimit = MaxForce;
        TorsoLift_HeadBase->AngularVelMax = FVector(0, 0, 3600);

        HeadBase->SetupAttachment(TorsoLift_HeadBase);
        HeadBase->SetRelativeLocation(FVector(0,0,0));
        HeadBase->SetRelativeRotation(FRotator(0, 0, 0));

        HeadBase_HeadTop->SetRelativeLocation(FVector(0.5, 0, 9.8));
        HeadBase_HeadTop->SetRelativeRotation(FRotator(0, 0, 0));
        HeadBase_HeadTop->LinearDOF = 0;
        HeadBase_HeadTop->RotationalDOF = 3;
        HeadBase_HeadTop->AngularForceLimit = MaxForce;
        HeadBase_HeadTop->AngularVelMax = FVector(0, 3600, 0);

        HeadTop->SetupAttachment(HeadBase_HeadTop);
        HeadTop->SetRelativeLocation(FVector(0,0,0));
        HeadTop->SetRelativeRotation(FRotator(0, 0, 0));

        TorsoLift_Arm1->SetRelativeLocation(FVector(15.505, 1.4, -15.1));
        TorsoLift_Arm1->SetRelativeRotation(FRotator(0,0,0));
        TorsoLift_Arm1->LinearDOF = 0;
        TorsoLift_Arm1->RotationalDOF = 2;
        TorsoLift_Arm1->AngularForceLimit = MaxForce;
        TorsoLift_Arm1->AngularVelMax = FVector(0, 0, 3600);

        Arm1->SetupAttachment(TorsoLift_Arm1);
        Arm1->SetRelativeLocation(FVector(0,0,0));
        Arm1->SetRelativeRotation(FRotator(0,0,0));

        Arm1_Arm2->SetRelativeLocation(FVector(12.5, 1.95, -3.1));
        Arm1_Arm2->SetRelativeRotation(FRotator(0,0,0));
        Arm1_Arm2->LinearDOF = 0;
        Arm1_Arm2->RotationalDOF = 3;
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
        Arm3_Arm4->RotationalDOF = 2;
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
        Arm5_Arm6->RotationalDOF = 2;
        Arm5_Arm6->AngularForceLimit = MaxForce;
        Arm5_Arm6->AngularVelMax = FVector(0, 0, 3600);

        Arm6->SetupAttachment(Arm5_Arm6);
        Arm6->SetRelativeLocation(FVector(0,0,0));
        Arm6->SetRelativeRotation(FRotator(0,0,0));
        
        return true;
    }
    else
    {
        return false;
    }
}

