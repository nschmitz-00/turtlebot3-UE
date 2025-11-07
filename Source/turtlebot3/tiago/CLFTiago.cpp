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
    AddLink(TEXT("base"), Base);
    AddLink(TEXT("wheel_left"), WheelLeft);
    AddLink(TEXT("wheel_right"), WheelRight);

    //Constraints
    Base_WheelLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_WheelLeft"));
    Base_WheelLeft->SetupAttachment(Base);

    Base_WheelRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_WheelRight"));
    Base_WheelRight->SetupAttachment(Base);

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
        AddJoint(TEXT("base"), TEXT("wheel_right"), TEXT("base_wheel_right"), Base_WheelRight);
        AddJoint(TEXT("base"), TEXT("wheel_left"), TEXT("base_wheel_left"), Base_WheelLeft);

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

        return true;
    }
    else
    {
        return false;
    }
}

