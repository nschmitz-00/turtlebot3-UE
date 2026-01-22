#include "TiagoTorsoKinematic.h"

ATiagoTorsoKinematic::ATiagoTorsoKinematic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ATiagoTorsoKinematic::SetupBody()
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

    //Joints
    Base_TorsoLift = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("Base_TorsoLift"));
    Base_TorsoLift->SetupAttachment(Base);

    TorsoLift_HeadBase = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("TorsoLift_HeadBase"));
    TorsoLift_HeadBase->SetupAttachment(TorsoLiftWithArm);

    HeadBase_HeadTop = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("HeadBase_HeadTop"));
    HeadBase_HeadTop->SetupAttachment(HeadBase);

    //Links
    AddLink(TEXT("torso_lift_link"), TorsoLiftWithArm);
    AddLink(TEXT("head_1_link"), HeadBase);
    AddLink(TEXT("head_2_link"), HeadTop);

    bBodyComponentsCreated = true;

    return true;
}

bool ATiagoTorsoKinematic::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        // ====================== Joints ==============================

        AddJoint(TEXT("base_link"), TEXT("torso_lift_link"), TEXT("torso_lift_joint"), Base_TorsoLift);
        AddJoint(TEXT("torso_lift_link"), TEXT("head_1_link"), TEXT("head_1_joint"), TorsoLift_HeadBase);
        AddJoint(TEXT("head_1_link"), TEXT("head_2_link"), TEXT("head_2_joint"), HeadBase_HeadTop);

        Base_TorsoLift->SetRelativeLocation(FVector(-6.2, 0, 79));
        Base_TorsoLift->SetRelativeRotation(FRotator(90,180,0));
        Base_TorsoLift->PositionMin = FVector(0,-1000,-1000);
        Base_TorsoLift->InitialPosition = FVector(InitialPosTorsoLiftInMeters * 100, 0, 0);
        Base_TorsoLift->LinearDOF = 1;
        Base_TorsoLift->RotationalDOF = 0;

        TorsoLift_HeadBase->SetRelativeLocation(FVector(18.2, 0, 0));
        TorsoLift_HeadBase->SetRelativeRotation(FRotator(90, 45, -45));
        TorsoLift_HeadBase->LinearDOF = 0;
        TorsoLift_HeadBase->RotationalDOF = 1;

        HeadBase_HeadTop->SetRelativeLocation(FVector(0.5, 0, 9.8));
        HeadBase_HeadTop->SetRelativeRotation(FRotator(0, 90, 0));
        HeadBase_HeadTop->LinearDOF = 0;
        HeadBase_HeadTop->RotationalDOF = 1;

        TorsoLiftWithArm->SetupAttachment(Base_TorsoLift);
        TorsoLiftWithArm->SetRelativeLocation(FVector(0,0,0));
        TorsoLiftWithArm->SetRelativeRotation(FRotator(90, 180, 0));

        HeadBase->SetupAttachment(TorsoLift_HeadBase);
        HeadBase->SetRelativeLocation(FVector(0,0,0));
        HeadBase->SetRelativeRotation(FRotator(0, -90, 90));

        HeadTop->SetupAttachment(HeadBase_HeadTop);
        HeadTop->SetRelativeLocation(FVector(0,0,0));
        HeadTop->SetRelativeRotation(FRotator(0, -90, 90));

        TorsoFix->SetRelativeLocation(FVector(-6.2, 0, 19.3));
        TorsoFix->SetupAttachment(Base);

        TorsoInnerBox->SetRelativeLocation(FVector(-6.2, 0, 19.3));
        TorsoInnerBox->SetupAttachment(Base);

        return true;
    }
    return false;
}


