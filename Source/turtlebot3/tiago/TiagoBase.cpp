#include "TiagoBaseOld.h"

DEFINE_LOG_CATEGORY(LogTiago);

ATiagoBaseOld::ATiagoBaseOld(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ROS2InterfaceClass = URRTiagoROS2InterfaceOld::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
    UE_LOG_WITH_INFO_SHORT(
        LogRapyutaCore, Warning, TEXT("%d, %d"), Base_LidarSensor == nullptr, !Base_LidarSensor->IsAttachedTo(LidarSensor));
}

bool ATiagoBaseOld::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }

    
    
    Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
    SetBaseMeshComp(Base, true, false);

    BaseRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseRing"));
    LidarSensor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidarSensor"));
    LidarComponent = CreateDefaultSubobject<URR2DLidarComponent>(TEXT("LidarComp"));
    WheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft"));
    WheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight"));
    CasterBackLeftBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBackLeftBase"));
    CasterBackRightBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBackRightBase"));
    CasterFrontLeftBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterFrontLeftBase"));
    CasterFrontRightBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterFrontRightBase"));
    CasterBackLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBackLeftWheel"));
    CasterBackRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBackRightWheel"));
    CasterFrontLeftWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterFrontLeftWheel"));
    CasterFrontRightWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterFrontRightWheel"));

    LidarComponent->SetupAttachment(LidarSensor);

    bBodyComponentsCreated = true;

    //Constraints
    Base_LidarSensor = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_LidarSensor"));
    Base_BaseRing = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_BaseRing"));

    Base_CasterBackLeftBase = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBackLeft"));
    Base_CasterBackRightBase = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterBackRight"));
    Base_CasterFrontLeftBase = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterFrontLeft"));
    Base_CasterFrontRightBase = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_CasterFrontRight"));
    CasterFrontLeftBase_CasterFrontLeftWheel = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("CasterFrontLeftBase_CasterFrontLeftWheel"));
    CasterFrontRightBase_CasterFrontRightWheel = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("CasterFrontRightBase_CasterFrontRightWheel"));
    CasterBackLeftBase_CasterBackLeftWheel = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("CasterBackLeftBase_CasterBackLeftWheel"));
    CasterBackRightBase_CasterBackRightWheel = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("CasterBackRightBase_CasterBackRightWheel"));

    return true;
}

void ATiagoBaseOld::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SetupWheelDrives();
}

void ATiagoBaseOld::SetupWheelDrives()
{
    UE_LOG_WITH_INFO_SHORT(LogRapyutaCore, Error, TEXT("This method should be implemented in child class"));
}

bool ATiagoBaseOld::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        Base->SetSimulatePhysics(true);

        BaseRing->SetSimulatePhysics(true);
        BaseRing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        LidarSensor->SetSimulatePhysics(true);
        LidarSensor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        
        WheelLeft->SetSimulatePhysics(true);
        WheelRight->SetSimulatePhysics(true);
        
        CasterFrontLeftBase->SetSimulatePhysics(true);
        CasterFrontLeftBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        CasterFrontRightBase->SetSimulatePhysics(true);
        CasterFrontRightBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        CasterBackLeftBase->SetSimulatePhysics(true);
        CasterBackLeftBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        CasterBackRightBase->SetSimulatePhysics(true);
        CasterBackRightBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        CasterFrontLeftWheel->SetSimulatePhysics(true);
        CasterFrontRightWheel->SetSimulatePhysics(true);
        CasterBackLeftWheel->SetSimulatePhysics(true);
        CasterBackRightWheel->SetSimulatePhysics(true);

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

        Base_BaseRing->ComponentName1.ComponentName = TEXT("Base");
        Base_BaseRing->ComponentName2.ComponentName = TEXT("BaseRing");
        Base_BaseRing->SetRelativeLocation(FVector(0, 0, 8));
        Base_BaseRing->SetDisableCollision(true);
        Base_BaseRing->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_BaseRing->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_BaseRing->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_BaseRing->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_BaseRing->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_BaseRing->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        /*
        CasterBackLeftBase_CasterBackLeftWheel->ComponentName1.ComponentName = TEXT("CasterBackLeftBase");
        CasterBackLeftBase_CasterBackLeftWheel->ComponentName2.ComponentName = TEXT("CasterBackLeftWheel");
        CasterBackLeftBase_CasterBackLeftWheel->SetRelativeLocation(FVector(-1.6, 0, -4));
        CasterBackLeftBase_CasterBackLeftWheel->SetDisableCollision(true);
        CasterBackLeftBase_CasterBackLeftWheel->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        CasterBackLeftBase_CasterBackLeftWheel->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        CasterBackLeftBase_CasterBackLeftWheel->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        CasterBackLeftBase_CasterBackLeftWheel->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        CasterBackLeftBase_CasterBackLeftWheel->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        CasterBackRightBase_CasterBackRightWheel->ComponentName1.ComponentName = TEXT("CasterBackRightBase");
        CasterBackRightBase_CasterBackRightWheel->ComponentName2.ComponentName = TEXT("CasterBackRightWheel");
        CasterBackRightBase_CasterBackRightWheel->SetRelativeLocation(FVector(-1.6, 0, -4));
        CasterBackRightBase_CasterBackRightWheel->SetDisableCollision(true);
        CasterBackRightBase_CasterBackRightWheel->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        CasterBackRightBase_CasterBackRightWheel->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        CasterBackRightBase_CasterBackRightWheel->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        CasterBackRightBase_CasterBackRightWheel->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        CasterBackRightBase_CasterBackRightWheel->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        CasterFrontLeftBase_CasterFrontLeftWheel->ComponentName1.ComponentName = TEXT("CasterFrontLeftBase");
        CasterFrontLeftBase_CasterFrontLeftWheel->ComponentName2.ComponentName = TEXT("CasterFrontLeftWheel");
        CasterFrontLeftBase_CasterFrontLeftWheel->SetRelativeLocation(FVector(-1.6, 0, -4));
        CasterFrontLeftBase_CasterFrontLeftWheel->SetDisableCollision(true);
        CasterFrontLeftBase_CasterFrontLeftWheel->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        CasterFrontLeftBase_CasterFrontLeftWheel->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        CasterFrontLeftBase_CasterFrontLeftWheel->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        CasterFrontLeftBase_CasterFrontLeftWheel->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        CasterFrontLeftBase_CasterFrontLeftWheel->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        CasterFrontRightBase_CasterFrontRightWheel->ComponentName1.ComponentName = TEXT("CasterFrontRightBase");
        CasterFrontRightBase_CasterFrontRightWheel->ComponentName2.ComponentName = TEXT("CasterFrontRightWheel");
        CasterFrontRightBase_CasterFrontRightWheel->SetRelativeLocation(FVector(-1.6, 0, -4));
        CasterFrontRightBase_CasterFrontRightWheel->SetDisableCollision(true);
        CasterFrontRightBase_CasterFrontRightWheel->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        CasterFrontRightBase_CasterFrontRightWheel->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        CasterFrontRightBase_CasterFrontRightWheel->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        CasterFrontRightBase_CasterFrontRightWheel->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        CasterFrontRightBase_CasterFrontRightWheel->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
*/
        Base_CasterBackLeftBase->ComponentName1.ComponentName = TEXT("Base");
        Base_CasterBackLeftBase->ComponentName2.ComponentName = TEXT("CasterBackLeftBase");
        Base_CasterBackLeftBase->SetRelativeLocation(FVector(-17.35, 10.2, -3));
        Base_CasterBackLeftBase->SetDisableCollision(true);
        Base_CasterBackLeftBase->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_CasterBackLeftBase->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_CasterBackLeftBase->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBackLeftBase->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBackLeftBase->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        Base_CasterBackRightBase->ComponentName1.ComponentName = TEXT("Base");
        Base_CasterBackRightBase->ComponentName2.ComponentName = TEXT("CasterBackRightBase");
        Base_CasterBackRightBase->SetRelativeLocation(FVector(-17.35, -10.2, -3));
        Base_CasterBackRightBase->SetDisableCollision(true);
        Base_CasterBackRightBase->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_CasterBackRightBase->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_CasterBackRightBase->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBackRightBase->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterBackRightBase->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        Base_CasterFrontLeftBase->ComponentName1.ComponentName = TEXT("Base");
        Base_CasterFrontLeftBase->ComponentName2.ComponentName = TEXT("CasterFrontLeftBase");
        Base_CasterFrontLeftBase->SetRelativeLocation(FVector(16.95, 10.2, -3));
        Base_CasterFrontLeftBase->SetDisableCollision(true);
        Base_CasterFrontLeftBase->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_CasterFrontLeftBase->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_CasterFrontLeftBase->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterFrontLeftBase->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterFrontLeftBase->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        Base_CasterFrontRightBase->ComponentName1.ComponentName = TEXT("Base");
        Base_CasterFrontRightBase->ComponentName2.ComponentName = TEXT("CasterFrontRightBase");
        Base_CasterFrontRightBase->SetRelativeLocation(FVector(16.95, -10.2, -3));
        Base_CasterFrontRightBase->SetDisableCollision(true);
        Base_CasterFrontRightBase->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_CasterFrontRightBase->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_CasterFrontRightBase->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterFrontRightBase->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
        Base_CasterFrontRightBase->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);
        /*

        CasterBackLeftWheel->SetupAttachment(CasterBackLeftBase_CasterBackLeftWheel);
        CasterBackRightWheel->SetupAttachment(CasterBackRightBase_CasterBackRightWheel);
        CasterFrontLeftWheel->SetupAttachment(CasterFrontLeftBase_CasterFrontLeftWheel);
        CasterFrontRightWheel->SetupAttachment(CasterFrontRightBase_CasterFrontRightWheel);

        CasterBackLeftBase_CasterBackLeftWheel->SetupAttachment(CasterBackLeftBase);
        CasterBackRightBase_CasterBackRightWheel->SetupAttachment(CasterBackRightBase);
        CasterFrontLeftBase_CasterFrontLeftWheel->SetupAttachment(CasterFrontLeftBase);
        CasterFrontRightBase_CasterFrontRightWheel->SetupAttachment(CasterFrontRightBase);
        */
        LidarSensor->SetupAttachment(Base_LidarSensor);
        BaseRing->SetupAttachment(Base_BaseRing);
        
        CasterBackLeftBase->SetupAttachment(Base_CasterBackLeftBase);
        CasterBackRightBase->SetupAttachment(Base_CasterBackRightBase);
        CasterFrontLeftBase->SetupAttachment(Base_CasterFrontLeftBase);
        CasterFrontRightBase->SetupAttachment(Base_CasterFrontRightBase);
        

        Base_LidarSensor->SetupAttachment(Base);
        Base_BaseRing->SetupAttachment(Base);

        
        Base_CasterBackLeftBase->SetupAttachment(Base);
        Base_CasterBackRightBase->SetupAttachment(Base);
        Base_CasterFrontLeftBase->SetupAttachment(Base);
        Base_CasterFrontRightBase->SetupAttachment(Base);
        

        return true;
    }
    else
    {
        UE_LOG_WITH_INFO_SHORT(LogTiago, Error, TEXT("Tiago not initialized - can't setup constraints!"));
        return false;
    }
}
