#include "Tiago.h"



DEFINE_LOG_CATEGORY(LogTiagoBlub);

ATiago::ATiago(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ROS2InterfaceClass = URRTiagoROS2Interface::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
    bBodyComponentsCreated = false;
    UE_LOG_WITH_INFO_SHORT(
        LogTiagoBlub,
        Warning,
        TEXT("%d, %d"),
        Base_LidarSensor == nullptr,
        !Base_LidarSensor->IsAttachedTo(LidarSensor));
    VehicleMoveComponentClass = UDifferentialDriveComponent::StaticClass();
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ATiago::SetupBody()
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
    BaseRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseRing"));

    //Antennas
    AntennaLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AntennaLeft"));
    AntennaRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AntennaRight"));
    
    // Lidar
    LidarSensor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidarSensor"));
    LidarComponent = CreateDefaultSubobject<URR2DLidarComponent>(TEXT("LidarComp"));
    LidarComponent->SetupAttachment(LidarSensor);
    
    // Wheels (Drive)
    WheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft"));
    WheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight"));
    
    // Torso
    TorsoFix = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoFix"));
    TorsoInnerBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoInnerBox"));
    TorsoLiftWithArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoLiftWithArm"));

    TorsoLiftJoint = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("TorsoLiftJoint"));
    TorsoLiftJoint->SetupAttachment(Base);

    
    AddLink(TEXT("torso_lift_link"), TorsoLiftWithArm);
    
    // ================== Base Constraints ==================
    
    Base_LidarSensor = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_LidarSensor"));
    Base_BaseRing = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_BaseRing"));
    Base_WheelLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_WheelLeft"));
    Base_WheelRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_WheelRight"));
    Base_AntennaLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_AntennaLeft"));
    Base_AntennaRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_AntennaRight"));
    Base_TorsoFix = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_TorsoFix"));
    Base_TorsoInnerBox = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_TorsoInnerBox"));
    
    bBodyComponentsCreated = true;

    return true;
}

void ATiago::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SetupWheelDrives();
}

void ATiago::SetupWheelDrives()
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

bool ATiago::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        // ======================== Physics ========================
        
        //Base
        Base->SetSimulatePhysics(true);
        //Base Ring
        BaseRing->SetSimulatePhysics(false);
        BaseRing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        //Lidar Sensor
        LidarSensor->SetSimulatePhysics(false);
        LidarSensor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        //Wheels
        WheelLeft->SetSimulatePhysics(true);
        WheelRight->SetSimulatePhysics(true);
        //Torso
        TorsoFix->SetSimulatePhysics(false);
        TorsoFix->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        TorsoInnerBox->SetSimulatePhysics(false);
        TorsoInnerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        TorsoLiftWithArm->SetSimulatePhysics(true);
        TorsoLiftWithArm->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        AddJoint(TEXT("base_link"), TEXT("torso_lift_link"), TEXT("TorsoLiftJoint"), TorsoLiftJoint);
        
        //Antennas
        AntennaLeft->SetSimulatePhysics(false);
        AntennaLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        AntennaRight->SetSimulatePhysics(false);
        AntennaRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
        Base_BaseRing->ComponentName1.ComponentName = TEXT("Base");
        Base_BaseRing->ComponentName2.ComponentName = TEXT("BaseRing");
        Base_BaseRing->SetRelativeLocation(FVector(0, 0, 8));
        Base_BaseRing->SetDisableCollision(true);
        Base_BaseRing->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_BaseRing->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_BaseRing->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
        Base_BaseRing->SetLinearZLimit(ELinearConstraintMotion::LCM_Locked, 0);

        BaseRing->SetupAttachment(Base_BaseRing);

        Base_BaseRing->SetupAttachment(Base);  
        
        //Antennas
        Base_AntennaLeft->ComponentName1.ComponentName = TEXT("Base");
        Base_AntennaLeft->ComponentName2.ComponentName = TEXT("AntennaLeft");
        Base_AntennaLeft->SetRelativeLocation(FVector(-20.1, -10.62, 19.5));
        Base_AntennaLeft->SetDisableCollision(true);
        Base_AntennaLeft->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_AntennaLeft->SetAngularTwistLimit(ACM_Locked, 0);
        Base_AntennaLeft->SetLinearZLimit(LCM_Locked, 0);

        Base_AntennaRight->ComponentName1.ComponentName = TEXT("Base");
        Base_AntennaRight->ComponentName2.ComponentName = TEXT("AntennaRight");
        Base_AntennaRight->SetRelativeLocation(FVector(-20.1, 10.62, 19.5));
        Base_AntennaRight->SetDisableCollision(true);
        Base_AntennaRight->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_AntennaRight->SetAngularTwistLimit(ACM_Locked, 0);
        Base_AntennaRight->SetLinearZLimit(LCM_Locked, 0);

        AntennaLeft->SetupAttachment(Base_AntennaLeft);
        AntennaRight->SetupAttachment(Base_AntennaRight);

        Base_AntennaLeft->SetupAttachment(Base);
        Base_AntennaRight->SetupAttachment(Base);

        //Torso
        Base_TorsoFix->ComponentName1.ComponentName = TEXT("Base");
        Base_TorsoFix->ComponentName2.ComponentName = TEXT("TorsoFix");
        Base_TorsoFix->SetRelativeLocation(FVector(-6.2, 0, 19.3));
        Base_TorsoFix->SetDisableCollision(true);
        Base_TorsoFix->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_TorsoFix->SetAngularTwistLimit(ACM_Locked, 0);
        Base_TorsoFix->SetLinearZLimit(LCM_Locked, 0);

        Base_TorsoInnerBox->ComponentName1.ComponentName = TEXT("Base");
        Base_TorsoInnerBox->ComponentName2.ComponentName = TEXT("TorsoInnerBox");
        Base_TorsoInnerBox->SetRelativeLocation(FVector(-6.2, 0, 0));
        Base_TorsoInnerBox->SetDisableCollision(true);
        Base_TorsoInnerBox->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_TorsoInnerBox->SetAngularTwistLimit(ACM_Locked, 0);
        Base_TorsoInnerBox->SetLinearZLimit(LCM_Locked, 0);

        TorsoFix->SetupAttachment(Base_TorsoFix);
        TorsoInnerBox->SetupAttachment(Base_TorsoInnerBox);

        Base_TorsoFix->SetupAttachment(Base);
        Base_TorsoInnerBox->SetupAttachment(Base);

        //Torso Joint
        TorsoLiftJoint->SetRelativeLocation(FVector(-6.2, 0, 79.0));
        TorsoLiftJoint->SetRelativeRotation(FRotator(0, 0,0));
        TorsoLiftJoint->LinearDOF = 3;
        TorsoLiftJoint->RotationalDOF = 0;
        TorsoLiftJoint->LinearForceLimit = 500.0f;
        TorsoLiftJoint->LinearDamper = 2000.0f;
        TorsoLiftJoint->LinearSpring = 100.0f;
        TorsoLiftJoint->LinearVelMax = FVector(0, 0, 3600);
        
        TorsoLiftWithArm->SetupAttachment(TorsoLiftJoint);
        
        return true;
    }
    else
    {
        return false;
    }
}

