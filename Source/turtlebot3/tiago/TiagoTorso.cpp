#include "TiagoTorso.h"

ATiagoTorso::ATiagoTorso(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ATiagoTorso::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }

    //Meshes
    TorsoFix = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoFix"));
    TorsoInnerBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoInnerBox"));
    TorsoLiftWithArm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorsoLiftWithArm"));

    HeadBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadBase"));
    HeadTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeadTop"));

    //Constraints
    Base_TorsoFix = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_TorsoFix"));
    Base_TorsoInnerBox = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Base_TorsoInnerBox"));

    //Joints
    Base_TorsoLift = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("Base_TorsoLift"));
    Base_TorsoLift->SetupAttachment(Base);

    TorsoLift_HeadBase = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("TorsoLift_HeadBase"));
    TorsoLift_HeadBase->SetupAttachment(TorsoLiftWithArm);

    HeadBase_HeadTop = CreateDefaultSubobject<URRPhysicsJointComponent>(TEXT("HeadBase_HeadTop"));
    HeadBase_HeadTop->SetupAttachment(HeadBase);

    //Links
    AddLink(TEXT("torso_lift_link"), TorsoLiftWithArm);
    AddLink(TEXT("head_1_link"), HeadBase);
    AddLink(TEXT("head_2_link"), HeadTop);

    bBodyComponentsCreated = true;

    return true;
}

bool ATiagoTorso::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        // ======================== Physic settings ====================

        TorsoFix->SetSimulatePhysics(true);
        TorsoInnerBox->SetSimulatePhysics(true);
        TorsoLiftWithArm->SetSimulatePhysics(true);
        HeadBase->SetSimulatePhysics(true);
        HeadTop->SetSimulatePhysics(true);

        // ======================== Constraints ========================

        Base_TorsoFix->ComponentName1.ComponentName = TEXT("Base");
        Base_TorsoFix->ComponentName2.ComponentName = TEXT("TorsoFix");
        Base_TorsoFix->SetRelativeLocation(FVector(-6.2, 0, 19.3));
        Base_TorsoFix->SetDisableCollision(true);
        Base_TorsoFix->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_TorsoFix->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_TorsoFix->SetAngularTwistLimit(ACM_Locked, 0);
        Base_TorsoFix->SetLinearXLimit(LCM_Locked, 0);
        Base_TorsoFix->SetLinearYLimit(LCM_Locked, 0);
        Base_TorsoFix->SetLinearZLimit(LCM_Locked, 0);

        Base_TorsoInnerBox->ComponentName1.ComponentName = TEXT("Base");
        Base_TorsoInnerBox->ComponentName2.ComponentName = TEXT("TorsoInnerBox");
        Base_TorsoInnerBox->SetRelativeLocation(FVector(-6.2, 0, 19.3));
        Base_TorsoInnerBox->SetDisableCollision(true);
        Base_TorsoInnerBox->SetAngularSwing1Limit(ACM_Locked, 0);
        Base_TorsoInnerBox->SetAngularSwing2Limit(ACM_Locked, 0);
        Base_TorsoInnerBox->SetAngularTwistLimit(ACM_Locked, 0);
        Base_TorsoInnerBox->SetLinearXLimit(LCM_Locked, 0);
        Base_TorsoInnerBox->SetLinearYLimit(LCM_Locked, 0);
        Base_TorsoInnerBox->SetLinearZLimit(LCM_Locked, 0);

        TorsoFix->SetupAttachment(Base_TorsoFix);
        TorsoInnerBox->SetupAttachment(Base_TorsoInnerBox);

        Base_TorsoFix->SetupAttachment(Base);
        Base_TorsoInnerBox->SetupAttachment(Base);
        
        // ====================== Joints ==============================

        AddJoint(TEXT("base_link"), TEXT("torso_lift_link"), TEXT("torso_lift_joint"), Base_TorsoLift);
        AddJoint(TEXT("torso_lift_link"), TEXT("head_1_link"), TEXT("head_1_joint"), TorsoLift_HeadBase);
        AddJoint(TEXT("head_1_link"), TEXT("head_2_link"), TEXT("head_2_joint"), HeadBase_HeadTop);

        Base_TorsoLift->SetRelativeLocation(FVector(-6.2, 0, 88.85));
        Base_TorsoLift->SetRelativeRotation(FRotator(-90,0,180));
        Base_TorsoLift->PositionMin = FVector(0,-1000,-1000);
        Base_TorsoLift->LinearDOF = 1;
        Base_TorsoLift->RotationalDOF = 0;
        Base_TorsoLift->LinearSpring = TorsoLinearSpring;
        Base_TorsoLift->LinearDamper = TorsoLinearDamper;
        Base_TorsoLift->bSmoothing = true;
        Base_TorsoLift->LinearVelocitySmoothingAcc = TorsoLinearVelSmoothingAcc;

        TorsoLiftWithArm->SetupAttachment(Base_TorsoLift);
        TorsoLiftWithArm->SetRelativeLocation(FVector(0,0,0));
        TorsoLiftWithArm->SetRelativeRotation(FRotator(-90, 0, 180));

        TorsoLift_HeadBase->SetRelativeLocation(FVector(18.2, 0, 0));
        TorsoLift_HeadBase->SetRelativeRotation(FRotator(90, 45, -45));
        TorsoLift_HeadBase->LinearDOF = 0;
        TorsoLift_HeadBase->RotationalDOF = 1;
        TorsoLift_HeadBase->AngularForceLimit = MaxForce;
        TorsoLift_HeadBase->AngularVelMax = FVector(3600, 0, 0);
        TorsoLift_HeadBase->AngularSpring = HeadAngularSpring;
        TorsoLift_HeadBase->AngularDamper = HeadAngularDamper;
        TorsoLift_HeadBase->bSmoothing = true;
        TorsoLift_HeadBase->AngularVelocitySmoothingAcc = HeadAngularVelSmoothingAcc;

        HeadBase->SetupAttachment(TorsoLift_HeadBase);
        HeadBase->SetRelativeLocation(FVector(0,0,0));
        HeadBase->SetRelativeRotation(FRotator(0, -90, 90));

        HeadBase_HeadTop->SetRelativeLocation(FVector(0.5, 0, 9.8));
        HeadBase_HeadTop->SetRelativeRotation(FRotator(0, 90, 0));
        HeadBase_HeadTop->LinearDOF = 0;
        HeadBase_HeadTop->RotationalDOF = 1;
        HeadBase_HeadTop->AngularForceLimit = MaxForce;
        HeadBase_HeadTop->AngularVelMax = FVector(3600, 0, 0);
        HeadBase_HeadTop->AngularSpring = HeadAngularSpring;
        HeadBase_HeadTop->AngularDamper = HeadAngularDamper;
        HeadBase_HeadTop->bSmoothing = true;
        HeadBase_HeadTop->AngularVelocitySmoothingAcc = HeadAngularVelSmoothingAcc;

        HeadTop->SetupAttachment(HeadBase_HeadTop);
        HeadTop->SetRelativeLocation(FVector(0,0,0));
        HeadTop->SetRelativeRotation(FRotator(0, -90, 90));
        
        return true;
    }
    return false;
}


