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
        
        return true;
    }
    else
    {
        return false;
    }
}

