#include "TiagoBase.h"

#include "Drives/DifferentialDriveComponent.h"

DEFINE_LOG_CATEGORY(LogTiago);

ATiagoBase::ATiagoBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ROS2InterfaceClass = URRTiagoROS2Interface::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
    UE_LOG_WITH_INFO_SHORT(
        LogTiago,
        Warning,
        TEXT("%d, %d"),
        Base_LidarSensor == nullptr,
        !Base_LidarSensor->IsAttachedTo(LidarSensor));
}

bool ATiagoBase::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }

    Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
    SetBaseMeshComp(Base, true, false);
    BaseMeshComp->BodyInstance.bLockXRotation = true;
    BaseMeshComp->BodyInstance.bLockYRotation = true;

    // BaseRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseRing"));
    LidarSensor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidarSensor"));
    LidarComponent = CreateDefaultSubobject<URR2DLidarComponent>(TEXT("LidarComp"));
    WheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft"));
    WheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight"));

    LidarComponent->SetupAttachment(LidarSensor);

    bBodyComponentsCreated = true;

    //Constraints
    Base_LidarSensor = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_LidarSensor"));
    // Base_BaseRing = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_BaseRing"));
    Base_WheelLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_WheelLeft"));
    Base_WheelRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_WheelRight"));

    return true;
}

void ATiagoBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SetupWheelDrives();
}

void ATiagoBase::SetupWheelDrives()
{
    if (bBodyComponentsCreated && IsValid(MovementComponent))
    {
        UDifferentialDriveComponent* diffDriveComponent = CastChecked<UDifferentialDriveComponent>(MovementComponent);
        diffDriveComponent->SetWheels(Base_WheelLeft, Base_WheelRight, WheelLeft, WheelRight);
        diffDriveComponent->WheelRadius = WheelRadius;
        diffDriveComponent->WheelSeparationHalf = WheelSeparationHalf;
        diffDriveComponent->SetPerimeter();
    }
}

bool ATiagoBase::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        Base->SetSimulatePhysics(true);

        // BaseRing->SetSimulatePhysics(true);
        // BaseRing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        LidarSensor->SetSimulatePhysics(false);
        LidarSensor->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        WheelLeft->SetSimulatePhysics(true);
        WheelRight->SetSimulatePhysics(true);

        Base_WheelLeft->ComponentName1.ComponentName = TEXT("Base");
        Base_WheelLeft->ComponentName2.ComponentName = TEXT("WheelLeft");
        Base_WheelLeft->SetDisableCollision(true);
        Base_WheelLeft->SetRelativeLocation(FVector(0, -20.22, 7.6));
        Base_WheelLeft->SetRelativeRotation(FRotator(0, -90, 0));
        Base_WheelLeft->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
        Base_WheelLeft->SetAngularDriveParams(MaxForce, MaxForce, MaxForce);
        Base_WheelLeft->SetAngularVelocityDriveTwistAndSwing(true, false);
        Base_WheelLeft->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_WheelLeft->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_WheelLeft->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_WheelLeft->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_WheelLeft->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        Base_WheelRight->ComponentName1.ComponentName = TEXT("Base");
        Base_WheelRight->ComponentName2.ComponentName = TEXT("WheelRight");
        Base_WheelRight->SetDisableCollision(true);
        Base_WheelRight->SetRelativeLocation(FVector(0, 20.22, 7.6));
        Base_WheelRight->SetRelativeRotation(FRotator(0, 90, 0));
        Base_WheelRight->SetAngularDriveMode(EAngularDriveMode::TwistAndSwing);
        Base_WheelRight->SetAngularDriveParams(MaxForce, MaxForce, MaxForce);
        Base_WheelRight->SetAngularVelocityDriveTwistAndSwing(true, false);
        Base_WheelRight->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_WheelRight->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_WheelRight->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_WheelRight->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_WheelRight->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        WheelLeft->SetupAttachment(Base_WheelLeft);
        WheelLeft->SetRelativeRotation(FRotator(0, -90, 0));
        WheelRight->SetupAttachment(Base_WheelRight);
        WheelRight->SetRelativeRotation(FRotator(0, 90, 0));

        Base_WheelRight->SetupAttachment(Base);
        Base_WheelLeft->SetupAttachment(Base);

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

        // Base_BaseRing->ComponentName1.ComponentName = TEXT("Base");
        // Base_BaseRing->ComponentName2.ComponentName = TEXT("BaseRing");
        // Base_BaseRing->SetRelativeLocation(FVector(0, 0, 8));
        // Base_BaseRing->SetDisableCollision(true);
        // Base_BaseRing->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        // Base_BaseRing->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        // Base_BaseRing->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        // Base_BaseRing->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        // Base_BaseRing->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        // Base_BaseRing->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        LidarSensor->SetupAttachment(Base_LidarSensor);
        // BaseRing->SetupAttachment(Base_BaseRing);

        Base_LidarSensor->SetupAttachment(Base);
        // Base_BaseRing->SetupAttachment(Base);        

        return true;
    }
    else
    {
        UE_LOG_WITH_INFO_SHORT(LogTiago, Error, TEXT("Tiago not initialized - can't setup constraints!"));
        return false;
    }
}