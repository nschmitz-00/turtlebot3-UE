#include "TiagoBaseKinematic.h"

#include "turtlebot3/tiago/Tools/MovingSoundComponent.h"

DEFINE_LOG_CATEGORY(LogTiagoKinematic);

ATiagoBaseKinematic::ATiagoBaseKinematic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ROS2InterfaceClass = UTiagoKinematicROS2Interface::StaticClass();
    VehicleMoveComponentClass = URRDifferentialDriveComponent::StaticClass();
    PrimaryActorTick.bCanEverTick = true;
    bBodyComponentsCreated = false;
    bInitializeJoints = true;
    SetupBody();
    SetupConstraintsAndPhysics();
    UE_LOG_WITH_INFO_SHORT(
        LogTiagoKinematic,
        Warning,
        TEXT("%d, %d"),
        Base_LidarSensor == nullptr,
        !Base_LidarSensor->IsAttachedTo(LidarSensor));
}

bool ATiagoBaseKinematic::SetupBody()
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

    //Dummys
    BaseFootprintDummy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseFootprintDummy"));
    SuspensionLeftDummy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuspensionLeftDummy"));
    SuspensionRightDummy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SuspensionRightDummy"));
    
    //Functional components
    AudioNode = CreateDefaultSubobject<UROS2AudioNode>(TEXT("AudioNode"));
    AudioNode->SetupAttachment(Base);

    LidarComponent = CreateDefaultSubobject<URR2DLidarComponent>(TEXT("LidarComp"));
    LidarComponent->SetupAttachment(LidarSensor);

    MovingSoundComponent = CreateDefaultSubobject<UMovingSoundComponent>(TEXT("MovingSoundComp"));
    MovingSoundComponent->SetupAttachment(Base);

    //Constraints
    Base_LidarSensor = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_LidarSensor"));

    //Joints
    Base_SuspensionLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_SuspensionLeft"));
    Base_SuspensionLeft->SetupAttachment(Base);

    Base_SuspensionRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_SuspensionRight"));
    Base_SuspensionRight->SetupAttachment(Base);
    
    SuspensionLeft_WheelLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("SuspensionLeft_WheelLeft"));
    SuspensionLeft_WheelLeft->SetupAttachment(SuspensionLeftDummy);

    SuspensionRight_WheelRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("SuspensionRight_WheelRight"));
    SuspensionRight_WheelRight->SetupAttachment(SuspensionRightDummy);

    Base_CasterBaseBackLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_CasterBaseBackLeft"));
    Base_CasterBaseBackLeft->SetupAttachment(Base);

    Base_CasterBaseBackRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_CasterBaseBackRight"));
    Base_CasterBaseBackRight->SetupAttachment(Base);

    Base_CasterBaseFrontLeft = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_CasterBaseFrontLeft"));
    Base_CasterBaseFrontLeft->SetupAttachment(Base);

    Base_CasterBaseFrontRight = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_CasterBaseFrontRight"));
    Base_CasterBaseFrontRight->SetupAttachment(Base);

    Base_Footprint = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("Base_Footprint"));
    Base_Footprint->SetupAttachment(Base);

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
    AddLink(TEXT("suspension_right_link"), SuspensionRightDummy);
    AddLink(TEXT("suspension_left_link"), SuspensionLeftDummy);
    AddLink(TEXT("base_footprint"), BaseFootprintDummy);
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
    AddLink(TEXT("base_antenna_left_link"), AntennaLeft);
    AddLink(TEXT("base_antenna_right_link"), AntennaRight);
    AddLink(TEXT("base_laser_link"), LidarSensor);
    AddLink(TEXT("base_sonar_01_link"), SonarLeft);
    AddLink(TEXT("base_sonar_02_link"), SonarCenter);
    AddLink(TEXT("base_sonar_03_link"), SonarRight);

    bBodyComponentsCreated = true;

    return true;    
}

void ATiagoBaseKinematic::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SetupWheelDrives();
}

void ATiagoBaseKinematic::SetupWheelDrives()
{
    if (bBodyComponentsCreated && IsValid(MovementComponent))
    {
        URRDifferentialDriveComponent* diffDriveComponent = CastChecked<URRDifferentialDriveComponent>(MovementComponent);
        diffDriveComponent->SetWheels(SuspensionLeft_WheelLeft, SuspensionRight_WheelRight);
        diffDriveComponent->WheelRadius = WheelRadius;
        diffDriveComponent->WheelSeparationHalf = WheelSeparationHalf;
        diffDriveComponent->SetPerimeter();
    }
}

bool ATiagoBaseKinematic::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        // ======================== Physic settings ====================
        
        Base->SetSimulatePhysics(true);
        Base->BodyInstance.SetMassOverride(100.0); //Seems like this doesn't work for some reason
        Base->SetCenterOfMass(FVector(0,0, -150)); // Same here...
        SuspensionRightDummy->SetSimulatePhysics(true);
        SuspensionLeftDummy->SetSimulatePhysics(true);
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

        // ======================== Simple Attachments =================

        BaseRing->SetRelativeLocation(FVector(0, 0, 4));
        BaseRing->SetupAttachment(Base);

        AntennaLeft->SetRelativeLocation(FVector(-20.1, -10.62, 19.5));
        AntennaLeft->SetupAttachment(Base);

        AntennaRight->SetRelativeLocation(FVector(-20.1, 10.62, 19.5));
        AntennaRight->SetupAttachment(Base);

        SonarLeft->SetRelativeLocation(FVector(-18.3, -18.3, 17.3));
        SonarLeft->SetRelativeRotation(FRotator(0, 45, 0));
        SonarLeft->SetupAttachment(Base);

        SonarCenter->SetRelativeLocation(FVector(-25.9, 0, 17.3));
        SonarCenter->SetupAttachment(Base);

        SonarRight->SetRelativeLocation(FVector(-18.3, 18.3, 17.3));
        SonarRight->SetRelativeRotation(FRotator(0, -45, 0));
        SonarRight->SetupAttachment(Base);

        // ====================== Joints ==============================

        AddJoint(TEXT("suspension_right_link"), TEXT("wheel_right_link"), TEXT("wheel_right_joint"), SuspensionRight_WheelRight);
        AddJoint(TEXT("suspension_left_link"), TEXT("wheel_left_link"), TEXT("wheel_left_joint"), SuspensionLeft_WheelLeft);
        AddJoint(TEXT("base_link"), TEXT("suspension_right_link"), TEXT("suspension_right_joint"), Base_SuspensionRight);
        AddJoint(TEXT("base_link"), TEXT("suspension_left_link"), TEXT("suspension_left_joint"), Base_SuspensionLeft);
        AddJoint(TEXT("base_link"), TEXT("caster_back_left_1_link"), TEXT("caster_back_left_1_joint"), Base_CasterBaseBackLeft);
        AddJoint(TEXT("base_link"), TEXT("caster_back_right_1_link"), TEXT("caster_back_right_1_joint"), Base_CasterBaseBackRight);
        AddJoint(TEXT("base_link"), TEXT("caster_front_left_1_link"), TEXT("caster_front_left_1_joint"), Base_CasterBaseFrontLeft);
        AddJoint(TEXT("base_link"), TEXT("caster_front_right_1_link"), TEXT("caster_front_right_1_joint"), Base_CasterBaseFrontRight);
        AddJoint(TEXT("caster_back_left_1_link"), TEXT("caster_back_left_2_link"), TEXT("caster_back_left_2_joint"), CasterBaseBackLeft_CasterRollBackLeft);
        AddJoint(TEXT("caster_back_right_1_link"), TEXT("caster_back_right_2_link"), TEXT("caster_back_right_2_joint"), CasterBaseBackRight_CasterRollBackRight);
        AddJoint(TEXT("caster_front_left_1_link"), TEXT("caster_front_left_2_link"), TEXT("caster_front_left_2_joint"), CasterBaseFrontLeft_CasterRollFrontLeft);
        AddJoint(TEXT("caster_front_right_1_link"), TEXT("caster_front_right_2_link"), TEXT("caster_front_right_2_joint"), CasterBaseFrontRight_CasterRollFrontRight);
        AddJoint(TEXT("base_footprint"), TEXT("base_link"), TEXT("base_footprint_joint"), Base_Footprint);

        Base_Footprint->LinearDOF = 0;
        Base_Footprint->RotationalDOF = 0;
        
        BaseFootprintDummy->SetupAttachment(Base_Footprint);
        
        //Wheels
        Base_SuspensionLeft->SetRelativeLocation(FVector(0, 0, 0));
        Base_SuspensionLeft->SetRelativeRotation(FRotator(0, 0, 0));
        Base_SuspensionLeft->LinearDOF = 0;
        Base_SuspensionLeft->RotationalDOF = 0;

        Base_SuspensionRight->SetRelativeLocation(FVector(0, 0, 0));
        Base_SuspensionRight->SetRelativeRotation(FRotator(0, 0, 0));
        Base_SuspensionRight->LinearDOF = 0;
        Base_SuspensionRight->RotationalDOF = 0;
        
        SuspensionLeft_WheelLeft->SetRelativeLocation(FVector(0, -20.22, 0));
        SuspensionLeft_WheelLeft->SetRelativeRotation(FRotator(0, -90, 0));
        SuspensionLeft_WheelLeft->LinearDOF = 0;
        SuspensionLeft_WheelLeft->RotationalDOF = 1;
        SuspensionLeft_WheelLeft->AngularForceLimit = MaxForce;
        SuspensionLeft_WheelLeft->AngularVelMax = FVector(3600, 0, 0);

        SuspensionRight_WheelRight->SetRelativeLocation(FVector(0, 20.22, 0));
        SuspensionRight_WheelRight->SetRelativeRotation(FRotator(0, 90, 0));
        SuspensionRight_WheelRight->LinearDOF = 0;
        SuspensionRight_WheelRight->RotationalDOF = 1;
        SuspensionRight_WheelRight->AngularForceLimit = MaxForce;
        SuspensionRight_WheelRight->AngularVelMax = FVector(3600, 0, 0);

        WheelLeft->SetupAttachment(SuspensionLeft_WheelLeft);
        WheelLeft->SetRelativeLocation(FVector(0, 0, 0));
        WheelLeft->SetRelativeRotation(FRotator(0, 180, 0));
        WheelRight->SetupAttachment(SuspensionRight_WheelRight);
        WheelRight->SetRelativeLocation(FVector(0, 0, 0));
        WheelRight->SetRelativeRotation(FRotator(0, -180, 0));

        SuspensionLeftDummy->SetupAttachment(Base_SuspensionLeft);
        SuspensionRightDummy->SetupAttachment(Base_SuspensionRight);

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
    UE_LOG_WITH_INFO(LogTiagoKinematic, Error, TEXT("Tiago not initialized - can't setup constraints!"));
    return false;
    
}



