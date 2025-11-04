#include "TiagoCasterBalls.h"

ATiagoCasterBalls::ATiagoCasterBalls(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    VehicleMoveComponentClass = UDifferentialDriveComponent::StaticClass();
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ATiagoCasterBalls::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }

    CasterBallFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBallFrontLeft"));
    CasterBallFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBallFrontRight"));
    CasterBallBackLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBallBackLeft"));
    CasterBallBackRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBallBackRight"));

    //Constraints
    Base_CasterBallFrontLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBallFrontLeft"));
    Base_CasterBallFrontRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBallFrontRight"));
    Base_CasterBallBackLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBallBackLeft"));
    Base_CasterBallBackRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBallBackRight"));

    bBodyComponentsCreated = true;

    return true;
}

bool ATiagoCasterBalls::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        //Caster balls
        Base_CasterBallBackLeft->ComponentName1.ComponentName = TEXT("Base");
        Base_CasterBallBackLeft->ComponentName2.ComponentName = TEXT("CasterBallBackLeft");
        Base_CasterBallBackLeft->SetRelativeLocation(FVector(-17.35, 10.2, -3));
        Base_CasterBallBackLeft->SetDisableCollision(true);
        Base_CasterBallBackLeft->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBallBackLeft->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBallBackLeft->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        Base_CasterBallBackRight->ComponentName1.ComponentName = TEXT("Base");
        Base_CasterBallBackRight->ComponentName2.ComponentName = TEXT("CasterBallBackRight");
        Base_CasterBallBackRight->SetRelativeLocation(FVector(-17.35, -10.2, -3));
        Base_CasterBallBackRight->SetDisableCollision(true);
        Base_CasterBallBackRight->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBallBackRight->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBallBackRight->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        Base_CasterBallFrontLeft->ComponentName1.ComponentName = TEXT("Base");
        Base_CasterBallFrontLeft->ComponentName2.ComponentName = TEXT("CasterBallFrontLeft");
        Base_CasterBallFrontLeft->SetRelativeLocation(FVector(16.95, 10.2, -3));
        Base_CasterBallFrontLeft->SetDisableCollision(true);
        Base_CasterBallFrontLeft->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBallFrontLeft->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBallFrontLeft->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        Base_CasterBallFrontRight->ComponentName1.ComponentName = TEXT("Base");
        Base_CasterBallFrontRight->ComponentName2.ComponentName = TEXT("CasterBallFrontRight");
        Base_CasterBallFrontRight->SetRelativeLocation(FVector(16.95, -10.2, -3));
        Base_CasterBallFrontRight->SetDisableCollision(true);
        Base_CasterBallFrontRight->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBallFrontRight->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBallFrontRight->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        CasterBallFrontLeft->SetupAttachment(Base_CasterBallFrontLeft);
        CasterBallFrontRight->SetupAttachment(Base_CasterBallFrontRight);
        CasterBallBackLeft->SetupAttachment(Base_CasterBallBackLeft);
        CasterBallBackRight->SetupAttachment(Base_CasterBallBackRight);

        Base_CasterBallFrontLeft->SetupAttachment(Base);
        Base_CasterBallFrontRight->SetupAttachment(Base);
        Base_CasterBallBackLeft->SetupAttachment(Base);
        Base_CasterBallBackRight->SetupAttachment(Base);
        
        return true;
    }
    else
    {
        return false;
    }
}

