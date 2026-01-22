#pragma once

#include "CoreMinimal.h"
#include "TiagoTorsoKinematic.h"
#include "Drives/RRKinematicJointComponent.h"

#include "TiagoArmKinematic.generated.h"

UCLASS()

class ATiagoArmKinematic : public ATiagoTorsoKinematic
{
    GENERATED_BODY()
    
public:
    ATiagoArmKinematic(const FObjectInitializer &ObjectInitializer);

protected:

    //Meshes
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Arm1 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Arm2 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Arm3 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Arm4 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Arm5 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Arm6 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Arm7Dummy = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* ArmTool = nullptr;

    //Joints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* TorsoLift_Arm1 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Arm1_Arm2 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Arm2_Arm3 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Arm3_Arm4 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Arm4_Arm5 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Arm5_Arm6 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Arm6_Arm7 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialRotArm1JointInRad = 0.2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialRotArm2JointInRad = -1.34;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialRotArm3JointInRad = -0.2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialRotArm4JointInRad = 1.94;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialRotArm5JointInRad = -1.57;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialRotArm6JointInRad = 1.37;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialRotArm7JointInRad = 0.0;

    virtual bool SetupBody() override;

    virtual bool SetupConstraintsAndPhysics() override;
    
};
