#include "CLFTiagoBase.h"

DEFINE_LOG_CATEGORY(LogCLFTiago);

ACLFTiagoBase::ACLFTiagoBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ROS2InterfaceClass = UCLFTiagoROS2Interface::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
    bBodyComponentsCreated = false;
    bInitializeJoints = true;
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

    // Base
    Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
    SetBaseMeshComp(Base, true, false);

    // Base Ring
    BaseRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseRing"));

    //Antennas
    AntennaLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AntennaLeft"));
    AntennaRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AntennaRight"));

    //Lidar
    LidarSensor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidarSensor"));
    LidarComponent = CreateDefaultSubobject<URR2DLidarComponent>(TEXT("LidarComp"));
    LidarComponent->SetupAttachment(LidarSensor);

    //Wheels
    WheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft"));
    WheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight"));

    //Caster
    CasterBase1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBase1"));
    CasterRoll1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterRoll1"));
    CasterBase2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBase2"));
    CasterRoll2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterRoll2"));
    CasterBase3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBase3"));
    CasterRoll3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterRoll3"));
    CasterBase4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBase4"));
    CasterRoll4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterRoll4"));

    // Torso
    TorsoFix = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoFix"));
    TorsoInnerBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoInnerBox"));
    TorsoLiftWithArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoLiftWithArm"));

    // Head
    HeadBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadBase"));
    HeadTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadTop"));

    // Arm
    Arm1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm1"));
    Arm2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm2"));
    Arm3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm3"));
    Arm4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm4"));
    Arm5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm5"));
    Arm6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm6"));
    
    // Gripper
    GripperLink = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperLink"));
    GripperLeftFingerLink = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperLeftFingerLink"));
    GripperRightFingerLink = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperRightFingerLink"));
    GripperFingerMountL = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerMountL"));
    GripperFingerMountR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerMountR"));
    GripperFingerL1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerL1"));
    GripperFingerR1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerR1"));
    GripperFingerR2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GripperFingerR2"));

    // Constraints
    Base_LidarSensor = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_LidarSensor"));
    Base_BaseRing = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_BaseRing"));
    Base_AntennaLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_AntennaLeft"));
    Base_AntennaRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_AntennaRight"));
    Base_TorsoFix = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_TorsoFix"));
    Base_TorsoInnerBox = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_TorsoInnerBox"));

    bBodyComponentsCreated = true;
    
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
        //Base
        Base->SetSimulatePhysics(true);
        //Base Ring
        BaseRing->SetSimulatePhysics(true);
        //Lidar Sensor
        LidarSensor->SetSimulatePhysics(true);
        //Wheels
        WheelLeft->SetSimulatePhysics(true);
        WheelRight->SetSimulatePhysics(true);
        //Caster
        CasterBase1->SetSimulatePhysics(true);
        CasterRoll1->SetSimulatePhysics(true);
        CasterBase2->SetSimulatePhysics(true);
        CasterRoll2->SetSimulatePhysics(true);
        CasterBase3->SetSimulatePhysics(true);
        CasterRoll3->SetSimulatePhysics(true);
        CasterBase4->SetSimulatePhysics(true);
        CasterRoll4->SetSimulatePhysics(true);
        //Torso
        TorsoFix->SetSimulatePhysics(true);
        TorsoInnerBox->SetSimulatePhysics(true);
        TorsoLiftWithArm->SetSimulatePhysics(true);
        //Antennas
        AntennaLeft->SetSimulatePhysics(true);
        AntennaRight->SetSimulatePhysics(true);
        //Head
        HeadBase->SetSimulatePhysics(true);
        HeadTop->SetSimulatePhysics(true);
        //Arm
        Arm1->SetSimulatePhysics(true);
        Arm2->SetSimulatePhysics(true);
        Arm3->SetSimulatePhysics(true);
        Arm4->SetSimulatePhysics(true);
        Arm5->SetSimulatePhysics(true);
        Arm6->SetSimulatePhysics(true);
        //Gripper
        GripperLink->SetSimulatePhysics(true);
        GripperLeftFingerLink->SetSimulatePhysics(true);
        GripperRightFingerLink->SetSimulatePhysics(true);
        GripperFingerMountL->SetSimulatePhysics(true);
        GripperFingerMountR->SetSimulatePhysics(true);
        GripperFingerL1->SetSimulatePhysics(true);
        GripperFingerR1->SetSimulatePhysics(true);
        GripperFingerR2->SetSimulatePhysics(true);
        
        // ======================== Constraints ========================

        //Lidar
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
        Base_TorsoInnerBox->SetRelativeLocation(FVector(-6.2, 0, 19.3));
        Base_TorsoInnerBox->SetDisableCollision(true);
        Base_TorsoInnerBox->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_TorsoInnerBox->SetAngularTwistLimit(ACM_Locked, 0);
        Base_TorsoInnerBox->SetLinearZLimit(LCM_Locked, 0);

        TorsoFix->SetupAttachment(Base_TorsoFix);
        TorsoInnerBox->SetupAttachment(Base_TorsoInnerBox);

        Base_TorsoFix->SetupAttachment(Base);
        Base_TorsoInnerBox->SetupAttachment(Base);

        return true;
    }
    else
    {
        UE_LOG_WITH_INFO(LogCLFTiago, Error, TEXT("Tiago not initialized - can't setup constraints!"));
        return false;
    }
}



