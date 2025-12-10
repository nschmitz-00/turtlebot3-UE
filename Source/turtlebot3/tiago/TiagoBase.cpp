#include "TiagoBase.h"

DEFINE_LOG_CATEGORY(LogTiago);

ATiagoBase::ATiagoBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ROS2InterfaceClass = UCLFTiagoROS2Interface::StaticClass();
    VehicleMoveComponentClass = URRDifferentialDriveComponent::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
    bBodyComponentsCreated = false;
    bInitializeJoints = true;
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

    //Meshes
    Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
    SetBaseMeshComp(Base, true, false);
    Base->BodyInstance.bLockXRotation = true;
    Base->BodyInstance.bLockYRotation = true;

    BaseRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseRing"));

    AntennaLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AntennaLeft"));
    AntennaRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AntennaRight"));

    LidarSensor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidarSensor"));
    LidarComponent = CreateDefaultSubobject<URR2DLidarComponent>(TEXT("LidarComp"));
    LidarComponent->SetupAttachment(LidarSensor);

    WheelLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelLeft"));
    WheelRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelRight"));

    CasterBaseBackLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBaseBackLeft"));
    CasterRollBackLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterRollBackLeft"));
    CasterBaseBackRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBaseBackRight"));
    CasterRollBackRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterRollBackRight"));
    CasterBaseFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBaseFrontLeft"));
    CasterRollFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterRollFrontLeft"));
    CasterBaseFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterBaseFrontRight"));
    CasterRollFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasterRollFrontRight"));

    SonarLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SonarLeft"));
    SonarCenter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SonarCenter"));
    SonarRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SonarRight"));

    //Constraints
    Base_LidarSensor = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_LidarSensor"));
    Base_BaseRing = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_BaseRing"));
    Base_AntennaLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_AntennaLeft"));
    Base_AntennaRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_AntennaRight"));
    Base_SonarLeft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_SonarLeft"));
    Base_SonarCenter = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_SonarCenter"));
    Base_SonarRight = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_SonarRight"));

    //Joints
    Base_WheelLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_WheelLeft"));
    Base_WheelLeft->SetupAttachment(Base);

    Base_WheelRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_WheelRight"));
    Base_WheelRight->SetupAttachment(Base);

    Base_CasterBaseBackLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_CasterBaseBackLeft"));
    Base_CasterBaseBackLeft->SetupAttachment(Base);

    Base_CasterBaseBackRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_CasterBaseBackRight"));
    Base_CasterBaseBackRight->SetupAttachment(Base);

    Base_CasterBaseFrontLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_CasterBaseFrontLeft"));
    Base_CasterBaseFrontLeft->SetupAttachment(Base);

    Base_CasterBaseFrontRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_CasterBaseFrontRight"));
    Base_CasterBaseFrontRight->SetupAttachment(Base);

    CasterBaseBackLeft_CasterRollBackLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(
        TEXT("CasterBaseBackLeft_CasterRollBackLeft"));
    CasterBaseBackLeft_CasterRollBackLeft->SetupAttachment(CasterBaseBackLeft);

    CasterBaseBackRight_CasterRollBackRight = CreateDefaultSubobject<URRPhysicsJointComponent>(
        TEXT("CasterBaseBackRight_CasterRollBackRight"));
    CasterBaseBackRight_CasterRollBackRight->SetupAttachment(CasterBaseBackRight);

    CasterBaseFrontLeft_CasterRollFrontLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(
        TEXT("CasterBaseFrontLeft_CasterRollFrontLeft"));
    CasterBaseFrontLeft_CasterRollFrontLeft->SetupAttachment(CasterBaseFrontLeft);

    CasterBaseFrontRight_CasterRollFrontRight = CreateDefaultSubobject<URRPhysicsJointComponent>(
        TEXT("CasterBaseFrontRight_CasterRollFrontRight"));
    CasterBaseFrontRight_CasterRollFrontRight->SetupAttachment(CasterBaseFrontRight);

    //Links
    AddLink(TEXT("base_link"), Base);
    AddLink(TEXT("suspension_right_link"), Base);
    AddLink(TEXT("suspension_left_link"), Base);
    AddLink(TEXT("wheel_left_link"), WheelLeft);
    AddLink(TEXT("wheel_right_link"), WheelRight);
    AddLink(TEXT("caster_back_left_1_link"), CasterBaseBackLeft);
    AddLink(TEXT("caster_back_left_2_link"), CasterRollBackLeft);
    AddLink(TEXT("caster_back_right_1_link"), CasterBaseBackRight);
    AddLink(TEXT("caster_back_right_2_link"), CasterRollBackRight);
    AddLink(TEXT("caster_front_left_1_link"), CasterBaseFrontLeft);
    AddLink(TEXT("caster_front_left_2_link"), CasterRollFrontLeft);
    AddLink(TEXT("caster_front_right_1_link"), CasterBaseFrontRight);
    AddLink(TEXT("caster_front_right_2_link"), CasterRollFrontRight);

    bBodyComponentsCreated = true;

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
        URRDifferentialDriveComponent* diffDriveComponent = CastChecked<URRDifferentialDriveComponent>(MovementComponent);
        diffDriveComponent->SetWheels(Base_WheelLeft, Base_WheelRight);
        diffDriveComponent->WheelRadius = WheelRadius;
        diffDriveComponent->WheelSeparationHalf = WheelSeparationHalf;
        diffDriveComponent->SetPerimeter();
    }
}

bool ATiagoBase::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        // ======================== Physic settings ====================
        
        Base->SetSimulatePhysics(true);
        Base->BodyInstance.SetMassOverride(100.0);
        Base->SetCenterOfMass(FVector(0,0, -150));
        BaseRing->SetSimulatePhysics(true);
        LidarSensor->SetSimulatePhysics(true);
        WheelLeft->SetSimulatePhysics(true);
        WheelLeft->BodyInstance.SetMassOverride(20.0);
        WheelRight->SetSimulatePhysics(true);
        WheelRight->BodyInstance.SetMassOverride(20.0);
        CasterBaseBackLeft->SetSimulatePhysics(true);
        CasterBaseBackLeft->BodyInstance.SetMassOverride(1.0);
        CasterRollBackLeft->SetSimulatePhysics(true);
        CasterRollBackLeft->BodyInstance.SetMassOverride(1.0);
        CasterBaseBackRight->SetSimulatePhysics(true);
        CasterBaseBackRight->BodyInstance.SetMassOverride(1.0);
        CasterRollBackRight->SetSimulatePhysics(true);
        CasterRollBackRight->BodyInstance.SetMassOverride(1.0);
        CasterBaseFrontLeft->SetSimulatePhysics(true);
        CasterBaseFrontLeft->BodyInstance.SetMassOverride(1.0);
        CasterRollFrontLeft->SetSimulatePhysics(true);
        CasterRollFrontLeft->BodyInstance.SetMassOverride(1.0);
        CasterBaseFrontRight->SetSimulatePhysics(true);
        CasterBaseFrontRight->BodyInstance.SetMassOverride(1.0);
        CasterRollFrontRight->SetSimulatePhysics(true);
        CasterRollFrontRight->BodyInstance.SetMassOverride(1.0);
        AntennaLeft->SetSimulatePhysics(true);
        AntennaRight->SetSimulatePhysics(true);
        SonarLeft->SetSimulatePhysics(true);
        SonarCenter->SetSimulatePhysics(true);
        SonarRight->SetSimulatePhysics(true);

        // =================== ROS Component Settings ==================

        LidarComponent->StartAngle = -90.0;
        LidarComponent->FOVHorizontal = 180.0;
        LidarComponent->MinRange = 1.0;
        LidarComponent->MaxRange = 2500.0;
        LidarComponent->bIgnoreSelf = true;
        LidarComponent->FrameId = "base_laser_link";

        // ======================== Constraints ========================

        //Lidar
        Base_LidarSensor->ComponentName1.ComponentName = TEXT("Base");
        Base_LidarSensor->ComponentName2.ComponentName = TEXT("LidarSensor");
        Base_LidarSensor->SetRelativeLocation(FVector(20.2, 0, -0.4));
        Base_LidarSensor->SetDisableCollision(true);
        Base_LidarSensor->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_LidarSensor->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_LidarSensor->SetAngularTwistLimit(ACM_Locked, 0);
        Base_LidarSensor->SetLinearXLimit(LCM_Locked, 0);
        Base_LidarSensor->SetLinearYLimit(LCM_Locked, 0);
        Base_LidarSensor->SetLinearZLimit(LCM_Locked, 0);

        LidarSensor->SetupAttachment(Base_LidarSensor);

        Base_LidarSensor->SetupAttachment(Base);

        //Base ring
        Base_BaseRing->ComponentName1.ComponentName = TEXT("Base");
        Base_BaseRing->ComponentName2.ComponentName = TEXT("BaseRing");
        Base_BaseRing->SetRelativeLocation(FVector(0, 0, 4));
        Base_BaseRing->SetDisableCollision(true);
        Base_BaseRing->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_BaseRing->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_BaseRing->SetAngularTwistLimit(ACM_Locked, 0);
        Base_BaseRing->SetLinearXLimit(LCM_Locked, 0);
        Base_BaseRing->SetLinearYLimit(LCM_Locked, 0);
        Base_BaseRing->SetLinearZLimit(LCM_Locked, 0);

        BaseRing->SetupAttachment(Base_BaseRing);

        Base_BaseRing->SetupAttachment(Base);

        //Antennas
        Base_AntennaLeft->ComponentName1.ComponentName = TEXT("Base");
        Base_AntennaLeft->ComponentName2.ComponentName = TEXT("AntennaLeft");
        Base_AntennaLeft->SetRelativeLocation(FVector(-20.1, -10.62, 19.5));
        Base_AntennaLeft->SetDisableCollision(true);
        Base_AntennaLeft->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_AntennaLeft->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_AntennaLeft->SetAngularTwistLimit(ACM_Locked, 0);
        Base_AntennaLeft->SetLinearXLimit(LCM_Locked, 0);
        Base_AntennaLeft->SetLinearYLimit(LCM_Locked, 0);
        Base_AntennaLeft->SetLinearZLimit(LCM_Locked, 0);

        Base_AntennaRight->ComponentName1.ComponentName = TEXT("Base");
        Base_AntennaRight->ComponentName2.ComponentName = TEXT("AntennaRight");
        Base_AntennaRight->SetRelativeLocation(FVector(-20.1, 10.62, 19.5));
        Base_AntennaRight->SetDisableCollision(true);
        Base_AntennaRight->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_AntennaRight->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_AntennaRight->SetAngularTwistLimit(ACM_Locked, 0);
        Base_AntennaRight->SetLinearXLimit(LCM_Locked, 0);
        Base_AntennaRight->SetLinearYLimit(LCM_Locked, 0);
        Base_AntennaRight->SetLinearZLimit(LCM_Locked, 0);

        AntennaLeft->SetupAttachment(Base_AntennaLeft);
        AntennaRight->SetupAttachment(Base_AntennaRight);

        Base_AntennaLeft->SetupAttachment(Base);
        Base_AntennaRight->SetupAttachment(Base);

        //Sonar sensors
        Base_SonarLeft->ComponentName1.ComponentName = TEXT("Base");
        Base_SonarLeft->ComponentName2.ComponentName = TEXT("SonarLeft");
        Base_SonarLeft->SetRelativeLocation(FVector(-18.3, -18.3, 17.3));
        Base_SonarLeft->SetRelativeRotation(FRotator(0,45,0));
        Base_SonarLeft->SetDisableCollision(true);
        Base_SonarLeft->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_SonarLeft->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_SonarLeft->SetAngularTwistLimit(ACM_Locked, 0);
        Base_SonarLeft->SetLinearXLimit(LCM_Locked, 0);
        Base_SonarLeft->SetLinearYLimit(LCM_Locked, 0);
        Base_SonarLeft->SetLinearZLimit(LCM_Locked, 0);

        Base_SonarCenter->ComponentName1.ComponentName = TEXT("Base");
        Base_SonarCenter->ComponentName2.ComponentName = TEXT("SonarCenter");
        Base_SonarCenter->SetRelativeLocation(FVector(-25.9, 0.0, 17.3));
        Base_SonarCenter->SetRelativeRotation(FRotator(0,0,0));
        Base_SonarCenter->SetDisableCollision(true);
        Base_SonarCenter->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_SonarCenter->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_SonarCenter->SetAngularTwistLimit(ACM_Locked, 0);
        Base_SonarCenter->SetLinearXLimit(LCM_Locked, 0);
        Base_SonarCenter->SetLinearYLimit(LCM_Locked, 0);
        Base_SonarCenter->SetLinearZLimit(LCM_Locked, 0);

        Base_SonarRight->ComponentName1.ComponentName = TEXT("Base");
        Base_SonarRight->ComponentName2.ComponentName = TEXT("SonarRight");
        Base_SonarRight->SetRelativeLocation(FVector(-18.3, 18.3, 17.3));
        Base_SonarRight->SetRelativeRotation(FRotator(0,-45,0));
        Base_SonarRight->SetDisableCollision(true);
        Base_SonarRight->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_SonarRight->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_SonarRight->SetAngularTwistLimit(ACM_Locked, 0);
        Base_SonarRight->SetLinearXLimit(LCM_Locked, 0);
        Base_SonarRight->SetLinearYLimit(LCM_Locked, 0);
        Base_SonarRight->SetLinearZLimit(LCM_Locked, 0);

        SonarLeft->SetupAttachment(Base_SonarLeft);
        SonarCenter->SetupAttachment(Base_SonarCenter);
        SonarRight->SetupAttachment(Base_SonarRight);

        Base_SonarLeft->SetupAttachment(Base);
        Base_SonarCenter->SetupAttachment(Base);
        Base_SonarRight->SetupAttachment(Base);

        // ====================== Joints ==============================

        AddJoint(TEXT("base_link"), TEXT("wheel_right_link"), TEXT("wheel_right_joint"), Base_WheelRight);
        AddJoint(TEXT("base_link"), TEXT("wheel_left_link"), TEXT("wheel_left_joint"), Base_WheelLeft);
        AddJoint(TEXT("base_link"), TEXT("caster_back_left_1_link"), TEXT("caster_back_left_1_joint"), Base_CasterBaseBackLeft);
        AddJoint(TEXT("base_link"), TEXT("caster_back_right_1_link"), TEXT("caster_back_right_1_joint"), Base_CasterBaseBackRight);
        AddJoint(TEXT("base_link"), TEXT("caster_front_left_1_link"), TEXT("caster_front_left_1_joint"), Base_CasterBaseFrontLeft);
        AddJoint(TEXT("base_link"), TEXT("caster_front_right_1_link"), TEXT("caster_front_right_1_joint"), Base_CasterBaseFrontRight);
        AddJoint(TEXT("caster_back_left_1_link"), TEXT("caster_back_left_2_link"), TEXT("caster_back_left_2_joint"), CasterBaseBackLeft_CasterRollBackLeft);
        AddJoint(TEXT("caster_back_right_1_link"), TEXT("caster_back_right_2_link"), TEXT("caster_back_right_2_joint"), CasterBaseBackRight_CasterRollBackRight);
        AddJoint(TEXT("caster_front_left_1_link"), TEXT("caster_front_left_2_link"), TEXT("caster_front_left_2_joint"), CasterBaseFrontLeft_CasterRollFrontLeft);
        AddJoint(TEXT("caster_front_right_1_link"), TEXT("caster_front_right_2_link"), TEXT("caster_front_right_2_joint"), CasterBaseFrontRight_CasterRollFrontRight);

        //Wheels
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

        WheelLeft->SetupAttachment(Base_WheelLeft);
        WheelLeft->SetRelativeLocation(FVector(0, 0, 0));
        WheelLeft->SetRelativeRotation(FRotator(0, 180, 0));
        WheelRight->SetupAttachment(Base_WheelRight);
        WheelRight->SetRelativeLocation(FVector(0, 0, 0));
        WheelRight->SetRelativeRotation(FRotator(0, -180, 0));

        //Caster
        //Back Left
        Base_CasterBaseBackLeft->SetRelativeLocation(FVector(-17.35,10.2,-3.35));
        Base_CasterBaseBackLeft->SetRelativeRotation(FRotator(90,0,0));
        Base_CasterBaseBackLeft->LinearDOF = 0;
        Base_CasterBaseBackLeft->RotationalDOF = 1;
        Base_CasterBaseBackLeft->AngularForceLimit = MaxForce;
        Base_CasterBaseBackLeft->AngularSpring = CasterBaseAngularSpring;
        Base_CasterBaseBackLeft->AngularDamper = CasterBaseAngularDamper;
        Base_CasterBaseBackLeft->AngularVelMax = FVector(3600, 0,0);
        
        CasterBaseBackLeft->SetupAttachment(Base_CasterBaseBackLeft);
        CasterBaseBackLeft->SetRelativeLocation(FVector(0,0,0));
        CasterBaseBackLeft->SetRelativeRotation(FRotator(0,0,0));
        
        CasterBaseBackLeft_CasterRollBackLeft->SetRelativeLocation(FVector(-4, 0, 1.6));
        CasterBaseBackLeft_CasterRollBackLeft->SetRelativeRotation(FRotator(0,-90,0));
        CasterBaseBackLeft_CasterRollBackLeft->LinearDOF = 0;
        CasterBaseBackLeft_CasterRollBackLeft->RotationalDOF = 1;
        CasterBaseBackLeft_CasterRollBackLeft->AngularForceLimit = MaxForce;
        CasterBaseBackLeft_CasterRollBackLeft->AngularSpring = CasterRollAngularSpring;
        CasterBaseBackLeft_CasterRollBackLeft->AngularDamper = CasterRollAngularDamper;
        CasterBaseBackLeft_CasterRollBackLeft->AngularVelMax = FVector(3600, 0, 0);
        
        CasterRollBackLeft->SetupAttachment(CasterBaseBackLeft_CasterRollBackLeft);
        CasterRollBackLeft->SetRelativeLocation(FVector(0,0,0));
        CasterRollBackLeft->SetRelativeRotation(FRotator(0,0,0));

        //Back Right
        Base_CasterBaseBackRight->SetRelativeLocation(FVector(-17.35,-10.2,-3.35));
        Base_CasterBaseBackRight->SetRelativeRotation(FRotator(90,0,0));
        Base_CasterBaseBackRight->LinearDOF = 0;
        Base_CasterBaseBackRight->RotationalDOF = 1;
        Base_CasterBaseBackRight->AngularForceLimit = MaxForce;
        Base_CasterBaseBackRight->AngularSpring = CasterBaseAngularSpring;
        Base_CasterBaseBackRight->AngularDamper = CasterBaseAngularDamper;
        Base_CasterBaseBackRight->AngularVelMax = FVector(3600, 0,0);
        
        CasterBaseBackRight->SetupAttachment(Base_CasterBaseBackRight);
        CasterBaseBackRight->SetRelativeLocation(FVector(0,0,0));
        CasterBaseBackRight->SetRelativeRotation(FRotator(0,0,0));
        
        CasterBaseBackRight_CasterRollBackRight->SetRelativeLocation(FVector(-4, 0, 1.6));
        CasterBaseBackRight_CasterRollBackRight->SetRelativeRotation(FRotator(0,-90,0));
        CasterBaseBackRight_CasterRollBackRight->LinearDOF = 0;
        CasterBaseBackRight_CasterRollBackRight->RotationalDOF = 1;
        CasterBaseBackRight_CasterRollBackRight->AngularForceLimit = MaxForce;
        CasterBaseBackRight_CasterRollBackRight->AngularSpring = CasterRollAngularSpring;
        CasterBaseBackRight_CasterRollBackRight->AngularDamper = CasterRollAngularDamper;
        CasterBaseBackRight_CasterRollBackRight->AngularVelMax = FVector(3600, 0, 0);
        
        CasterRollBackRight->SetupAttachment(CasterBaseBackRight_CasterRollBackRight);
        CasterRollBackRight->SetRelativeLocation(FVector(0,0,0));
        CasterRollBackRight->SetRelativeRotation(FRotator(0,0,0));
        
        //Front Left
        Base_CasterBaseFrontLeft->SetRelativeLocation(FVector(16.95,10.2,-3.35));
        Base_CasterBaseFrontLeft->SetRelativeRotation(FRotator(90,0,0));
        Base_CasterBaseFrontLeft->LinearDOF = 0;
        Base_CasterBaseFrontLeft->RotationalDOF = 1;
        Base_CasterBaseFrontLeft->AngularForceLimit = MaxForce;
        Base_CasterBaseFrontLeft->AngularSpring = CasterBaseAngularSpring;
        Base_CasterBaseFrontLeft->AngularDamper = CasterBaseAngularDamper;
        Base_CasterBaseFrontLeft->AngularVelMax = FVector(3600, 0,0);
        
        CasterBaseFrontLeft->SetupAttachment(Base_CasterBaseFrontLeft);
        CasterBaseFrontLeft->SetRelativeLocation(FVector(0,0,0));
        CasterBaseFrontLeft->SetRelativeRotation(FRotator(0,0,0));
        
        CasterBaseFrontLeft_CasterRollFrontLeft->SetRelativeLocation(FVector(-4, 0, 1.6));
        CasterBaseFrontLeft_CasterRollFrontLeft->SetRelativeRotation(FRotator(0,-90,0));
        CasterBaseFrontLeft_CasterRollFrontLeft->LinearDOF = 0;
        CasterBaseFrontLeft_CasterRollFrontLeft->RotationalDOF = 1;
        CasterBaseFrontLeft_CasterRollFrontLeft->AngularForceLimit = MaxForce;
        CasterBaseFrontLeft_CasterRollFrontLeft->AngularSpring = CasterRollAngularSpring;
        CasterBaseFrontLeft_CasterRollFrontLeft->AngularDamper = CasterRollAngularDamper;
        CasterBaseFrontLeft_CasterRollFrontLeft->AngularVelMax = FVector(3600, 0, 0);
        
        CasterRollFrontLeft->SetupAttachment(CasterBaseFrontLeft_CasterRollFrontLeft);
        CasterRollFrontLeft->SetRelativeLocation(FVector(0,0,0));
        CasterRollFrontLeft->SetRelativeRotation(FRotator(0,0,0));
        
        //Front Right
        Base_CasterBaseFrontRight->SetRelativeLocation(FVector(16.95,-10.2,-3.35));
        Base_CasterBaseFrontRight->SetRelativeRotation(FRotator(90,0,0));
        Base_CasterBaseFrontRight->LinearDOF = 0;
        Base_CasterBaseFrontRight->RotationalDOF = 1;
        Base_CasterBaseFrontRight->AngularForceLimit = MaxForce;
        Base_CasterBaseFrontRight->AngularSpring = CasterBaseAngularSpring;
        Base_CasterBaseFrontRight->AngularDamper = CasterBaseAngularDamper;
        Base_CasterBaseFrontRight->AngularVelMax = FVector(3600, 0,0);
        
        CasterBaseFrontRight->SetupAttachment(Base_CasterBaseFrontRight);
        CasterBaseFrontRight->SetRelativeLocation(FVector(0,0,0));
        CasterBaseFrontRight->SetRelativeRotation(FRotator(0,0,0));
        
        CasterBaseFrontRight_CasterRollFrontRight->SetRelativeLocation(FVector(-4, 0, 1.6));
        CasterBaseFrontRight_CasterRollFrontRight->SetRelativeRotation(FRotator(0,-90,0));
        CasterBaseFrontRight_CasterRollFrontRight->LinearDOF = 0;
        CasterBaseFrontRight_CasterRollFrontRight->RotationalDOF = 1;
        CasterBaseFrontRight_CasterRollFrontRight->AngularForceLimit = MaxForce;
        CasterBaseFrontRight_CasterRollFrontRight->AngularSpring = CasterRollAngularSpring;
        CasterBaseFrontRight_CasterRollFrontRight->AngularDamper = CasterRollAngularDamper;
        CasterBaseFrontRight_CasterRollFrontRight->AngularVelMax = FVector(3600, 0, 0);
        
        CasterRollFrontRight->SetupAttachment(CasterBaseFrontRight_CasterRollFrontRight);
        CasterRollFrontRight->SetRelativeLocation(FVector(0,0,0));
        CasterRollFrontRight->SetRelativeRotation(FRotator(0,0,0));

        return true;
        
    }
    UE_LOG_WITH_INFO(LogTiago, Error, TEXT("Tiago not initialized - can't setup constraints!"));
    return false;
}