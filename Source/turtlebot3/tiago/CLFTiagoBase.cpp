#include "CLFTiagoBase.h"

DEFINE_LOG_CATEGORY(LogCLFTiago);

ACLFTiagoBase::ACLFTiagoBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ROS2InterfaceClass = UCLFTiagoROS2Interface::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
    UE_LOG_WITH_INFO_SHORT(
        LogCLFTiago, Warning, TEXT("%d, %d"), Base_LidarSensor == nullptr, !Base_LidarSensor->IsAttachedTo(LidarSensor));
}

bool ACLFTiagoBase::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }

    Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
    SetBaseMeshComp(Base, true, false);

    LidarSensor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidarSensor"));
    LidarComponent = CreateDefaultSubobject<URR2DLidarComponent>(TEXT("LidarComp"));
    WheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft"));
    WheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight"));

    LidarComponent->SetupAttachment(LidarSensor);

    bBodyComponentsCreated = true;

    // Constraints
    Base_LidarSensor = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_LidarSensor"));

    return true;
}

void ACLFTiagoBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SetupWheelDrives();
}

void ACLFTiagoBase::SetupWheelDrives()
{
    UE_LOG_WITH_INFO_SHORT(LogCLFTiago, Error, TEXT("This method should be implemented in child class."));
}

bool ACLFTiagoBase::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        Base->SetSimulatePhysics(true);
        LidarSensor->SetSimulatePhysics(true);
        WheelLeft->SetSimulatePhysics(true);
        WheelRight->SetSimulatePhysics(true);

        Base_LidarSensor->ComponentName1.ComponentName = TEXT("Base");
        Base_LidarSensor->ComponentName2.ComponentName = TEXT("LidarSensor");
        Base_LidarSensor->SetRelativeLocation(FVector(20.2, 0, 0.4));
        Base_LidarSensor->SetDisableCollision(true);
        Base_LidarSensor->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_LidarSensor->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_LidarSensor->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_LidarSensor->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_LidarSensor->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_LidarSensor->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        LidarSensor->SetupAttachment(Base_LidarSensor);

        Base_LidarSensor->SetupAttachment(Base);

        return true;
    }
    else
    {
        UE_LOG_WITH_INFO(LogCLFTiago, Error, TEXT("Tiago not initialized - can't setup constraints!"));
        return false;
    }
}



