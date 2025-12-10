#pragma once

// UE Imports
#include "CoreMinimal.h"

//RapyutaSimulationPlugins
#include "TiagoTorso.h"
#include "Drives/RRPhysicsJointComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "TiagoArm.generated.h"

UCLASS()

class RAPYUTASIMULATIONPLUGINS_API ATiagoArm : public ATiagoTorso
{
    GENERATED_BODY()
    
public:
    ATiagoArm(const FObjectInitializer& ObjectInitializer);

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
    
    //Constraints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Arm7_ArmTool;

    //Joints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* TorsoLift_Arm1 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Arm1_Arm2 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Arm2_Arm3 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Arm3_Arm4 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Arm4_Arm5 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Arm5_Arm6 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Arm6_Arm7 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArmAngularSpring = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArmAngularDamper = 100.f;

    virtual bool SetupBody() override;

    virtual bool SetupConstraintsAndPhysics() override;
};
