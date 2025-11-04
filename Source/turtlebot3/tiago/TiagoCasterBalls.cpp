#include "TiagoCasterBalls.h"



DEFINE_LOG_CATEGORY(LogTiago);

ATiagoCasterBalls::ATiagoCasterBalls(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ROS2InterfaceClass = URRTiagoROS2Interface::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
    bBodyComponentsCreated = false;
    UE_LOG_WITH_INFO_SHORT(
        LogTiago,
        Warning,
        TEXT("%d, %d"),
        Base_LidarSensor == nullptr,
        !Base_LidarSensor->IsAttachedTo(LidarSensor));
    VehicleMoveComponentClass = UDifferentialDriveComponent::StaticClass();
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ATiagoCasterBalls::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }
    // ================== Base Components ==================
    
    // Base
    Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
    SetBaseMeshComp(Base, true, false);
    BaseMeshComp->BodyInstance.bLockXRotation = true;
    BaseMeshComp->BodyInstance.bLockYRotation = true;
    
    // Base Ring
    // BaseRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseRing"));
    
    // Lidar
    LidarSensor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidarSensor"));
    LidarComponent = CreateDefaultSubobject<URR2DLidarComponent>(TEXT("LidarComp"));
    LidarComponent->SetupAttachment(LidarSensor);
    
    // Wheels (Drive)
    WheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft"));
    WheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight"));
    
    // Wheels (Caster)
    CasterBallFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBallFrontLeft"));
    CasterBallFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBallFrontRight"));
    CasterBallBackLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBallBackLeft"));
    CasterBallBackRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBallBackRight"));
    
    // ================== Base Constraints ==================
    
    Base_LidarSensor = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_LidarSensor"));
    // Base_BaseRing = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_BaseRing"));
    Base_WheelLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_WheelLeft"));
    Base_WheelRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_WheelRight"));
    Base_CasterBallFrontLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBallFrontLeft"));
    Base_CasterBallFrontRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBallFrontRight"));
    Base_CasterBallBackLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBallBackLeft"));
    Base_CasterBallBackRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBallBackRight"));

    bBodyComponentsCreated = true;

    return true;
}

void ATiagoCasterBalls::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SetupWheelDrives();
}

void ATiagoCasterBalls::SetupWheelDrives()
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

bool ATiagoCasterBalls::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        // ======================== Physics ========================
        
        //Base
        Base->SetSimulatePhysics(true);
        //Base Ring
        // BaseRing->SetSimulatePhysics(true);
        // BaseRing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        //Lidar Sensor
        LidarSensor->SetSimulatePhysics(true);
        //Wheels
        WheelLeft->SetSimulatePhysics(true);
        WheelRight->SetSimulatePhysics(true);
        //Caster balls
        CasterBallFrontLeft->SetSimulatePhysics(true);
        CasterBallFrontRight->SetSimulatePhysics(true);
        CasterBallBackLeft->SetSimulatePhysics(true);
        CasterBallBackRight->SetSimulatePhysics(true);

        // ======================== Constraints ========================

        // Wheels
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

        //Lidar sensor
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

        //Base ring
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

        // BaseRing->SetupAttachment(Base_BaseRing);

        // Base_BaseRing->SetupAttachment(Base);  
        
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

        
        CasterBallFrontRight->SetupAttachment(Base_CasterBallFrontRight);
        CasterBallBackLeft->SetupAttachment(Base_CasterBallBackLeft);
        CasterBallBackRight->SetupAttachment(Base_CasterBallBackRight);
        CasterBallFrontLeft->SetupAttachment(Base_CasterBallFrontLeft);

        
        Base_CasterBallFrontRight->SetupAttachment(Base);
        Base_CasterBallBackLeft->SetupAttachment(Base);
        Base_CasterBallBackRight->SetupAttachment(Base);
        Base_CasterBallFrontLeft->SetupAttachment(Base);
        
        return true;
    }
    else
    {
        return false;
    }
}

