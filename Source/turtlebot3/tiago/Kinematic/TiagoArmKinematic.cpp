#include "TiagoArmKinematic.h"

ATiagoArmKinematic::ATiagoArmKinematic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    bBodyComponentsCreated = false;
    SetupBody();
    SetupConstraintsAndPhysics();
}

bool ATiagoArmKinematic::SetupBody()
{
    if (bBodyComponentsCreated)
    {
        return false;
    }

    //Meshes
    Arm1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm1"));
    Arm2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm2"));
    Arm3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm3"));
    Arm4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm4"));
    Arm5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm5"));
    Arm6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm6"));
    Arm7Dummy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arm7Dummy"));
    ArmTool = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmTool"));

    TorsoLift_Arm1 = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("TorsoLift_Arm1"));
    TorsoLift_Arm1->SetupAttachment(TorsoLiftWithArm);

    Arm1_Arm2 = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("Arm1_Arm2"));
    Arm1_Arm2->SetupAttachment(Arm1);

    Arm2_Arm3 = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("Arm2_Arm3"));
    Arm2_Arm3->SetupAttachment(Arm2);

    Arm3_Arm4 = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("Arm3_Arm4"));
    Arm3_Arm4->SetupAttachment(Arm3);

    Arm4_Arm5 = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("Arm4_Arm5"));
    Arm4_Arm5->SetupAttachment(Arm4);

    Arm5_Arm6 = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("Arm5_Arm6"));
    Arm5_Arm6->SetupAttachment(Arm5);

    Arm6_Arm7 = CreateDefaultSubobject<URRKinematicJointComponent>(TEXT("Arm6_Arm7"));
    Arm6_Arm7->SetupAttachment(Arm6);

    //Links
    AddLink(TEXT("arm_1_link"), Arm1);
    AddLink(TEXT("arm_2_link"), Arm2);
    AddLink(TEXT("arm_3_link"), Arm3);
    AddLink(TEXT("arm_4_link"), Arm4);
    AddLink(TEXT("arm_5_link"), Arm5);
    AddLink(TEXT("arm_6_link"), Arm6);
    AddLink(TEXT("arm_7_link"), Arm7Dummy);
    AddLink(TEXT("arm_tool_link"), ArmTool);

    bBodyComponentsCreated = true;

    return true;
}

bool ATiagoArmKinematic::SetupConstraintsAndPhysics()
{
    if (bBodyComponentsCreated)
    {
        AddJoint(TEXT("torso_lift_link"), TEXT("arm_1_link"), TEXT("arm_1_joint"), TorsoLift_Arm1);
        AddJoint(TEXT("arm_1_link"), TEXT("arm_2_link"), TEXT("arm_2_joint"), Arm1_Arm2);
        AddJoint(TEXT("arm_2_link"), TEXT("arm_3_link"), TEXT("arm_3_joint"), Arm2_Arm3);
        AddJoint(TEXT("arm_3_link"), TEXT("arm_4_link"), TEXT("arm_4_joint"), Arm3_Arm4);
        AddJoint(TEXT("arm_4_link"), TEXT("arm_5_link"), TEXT("arm_5_joint"), Arm4_Arm5);
        AddJoint(TEXT("arm_5_link"), TEXT("arm_6_link"), TEXT("arm_6_joint"), Arm5_Arm6);
        AddJoint(TEXT("arm_6_link"), TEXT("arm_7_link"), TEXT("arm_7_joint"), Arm6_Arm7);
    }

    TorsoLift_Arm1->SetRelativeLocation(FVector(15.505, -1.4, -15.1));
    TorsoLift_Arm1->SetRelativeRotation(FRotator(90, 0, 0));
    TorsoLift_Arm1->InitialOrientation = FRotator(0, 0, FMath::RadiansToDegrees(InitialRotArm1JointInRad));
    TorsoLift_Arm1->LinearDOF = 0;
    TorsoLift_Arm1->RotationalDOF = 1;

    Arm1_Arm2->SetRelativeLocation(FVector(12.5, -1.95, -3.1));
    Arm1_Arm2->SetRelativeRotation(FRotator(0,90,-90));
    Arm1_Arm2->InitialOrientation = FRotator(0, 0, FMath::RadiansToDegrees(InitialRotArm2JointInRad));
    Arm1_Arm2->LinearDOF = 0;
    Arm1_Arm2->RotationalDOF = 1;

    Arm2_Arm3->SetRelativeLocation(FVector(8.9, 0, -0.15));
    Arm2_Arm3->SetRelativeRotation(FRotator(0,180,180));
    Arm2_Arm3->InitialOrientation = FRotator(0, 0, FMath::RadiansToDegrees(InitialRotArm3JointInRad));
    Arm2_Arm3->LinearDOF = 0;
    Arm2_Arm3->RotationalDOF = 1;

    Arm3_Arm4->SetRelativeLocation(FVector(-2, 2.7, -22.2));
    Arm3_Arm4->SetRelativeRotation(FRotator(0,-90,90));
    Arm3_Arm4->InitialOrientation = FRotator(0, 0, FMath::RadiansToDegrees(InitialRotArm4JointInRad));
    Arm3_Arm4->LinearDOF = 0;
    Arm3_Arm4->RotationalDOF = 1;

    Arm4_Arm5->SetRelativeLocation(FVector(-16.2, -2, 2.7));
    Arm4_Arm5->SetRelativeRotation(FRotator(0,180,270));
    Arm4_Arm5->InitialOrientation = FRotator(0, 0, FMath::RadiansToDegrees(InitialRotArm5JointInRad));
    Arm4_Arm5->LinearDOF = 0;
    Arm4_Arm5->RotationalDOF = 1;

    Arm5_Arm6->SetRelativeLocation(FVector(0, 0, 15));
    Arm5_Arm6->SetRelativeRotation(FRotator(0,-90,-270));
    Arm5_Arm6->InitialOrientation = FRotator(0, 0, FMath::RadiansToDegrees(InitialRotArm6JointInRad));
    Arm5_Arm6->LinearDOF = 0;
    Arm5_Arm6->RotationalDOF = 1;

    Arm6_Arm7->SetRelativeLocation(FVector(1,0,0));
    Arm6_Arm7->SetRelativeRotation(FRotator(0,0,-90));
    Arm6_Arm7->InitialOrientation = FRotator(0, 0, FMath::RadiansToDegrees(InitialRotArm7JointInRad));
    Arm6_Arm7->LinearDOF = 0;
    Arm6_Arm7->RotationalDOF = 1;

    Arm1->SetupAttachment(TorsoLift_Arm1);
    Arm1->SetRelativeLocation(FVector(0,0,0));
    Arm1->SetRelativeRotation(FRotator(0, 90, -90));

    Arm2->SetupAttachment(Arm1_Arm2);
    Arm2->SetRelativeLocation(FVector(0,0,0));
    Arm2->SetRelativeRotation(FRotator(90,-120,60));

    Arm3->SetupAttachment(Arm2_Arm3);
    Arm3->SetRelativeLocation(FVector(0,0,0));
    Arm3->SetRelativeRotation(FRotator(0,-90,90));

    Arm4->SetupAttachment(Arm3_Arm4);
    Arm4->SetRelativeLocation(FVector(0,0,0));
    Arm4->SetRelativeRotation(FRotator(0,-90,90));

    Arm5->SetupAttachment(Arm4_Arm5);
    Arm5->SetRelativeLocation(FVector(0,0,0));
    Arm5->SetRelativeRotation(FRotator(0,-270,270));

    Arm6->SetupAttachment(Arm5_Arm6);
    Arm6->SetRelativeLocation(FVector(0,0,0));
    Arm6->SetRelativeRotation(FRotator(0,-90,-270));

    Arm7Dummy->SetupAttachment(Arm6_Arm7);
    Arm7Dummy->SetRelativeLocation(FVector(0,0,0));
    Arm7Dummy->SetRelativeRotation(FRotator(0,0,0));

    ArmTool->SetupAttachment(Arm7Dummy);
    ArmTool->SetRelativeLocation(FVector(4.85, 0, 0));
    ArmTool->SetRelativeRotation(FRotator(0, 90, -90));

    return true;
}


