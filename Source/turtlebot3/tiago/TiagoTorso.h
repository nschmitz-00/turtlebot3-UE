#pragma once

// UE Imports
#include "CoreMinimal.h"

//RapyutaSimulationPlugins
#include "TiagoBase.h"
#include "Drives/RRPhysicsJointComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "TiagoTorso.generated.h"

UCLASS()

class RAPYUTASIMULATIONPLUGINS_API ATiagoTorso : public ATiagoBase
{
    GENERATED_BODY()
    
public:
    ATiagoTorso(const FObjectInitializer& ObjectInitializer);

protected:

    //Meshes
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* TorsoFix = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* TorsoInnerBox = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* TorsoLiftWithArm = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* HeadBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* HeadTop = nullptr;

    //Constraints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_TorsoFix = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_TorsoInnerBox = nullptr;    
    
    //Joints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_TorsoLift = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* TorsoLift_HeadBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* HeadBase_HeadTop = nullptr;

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TorsoLinearSpring = 1000000.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TorsoLinearDamper = 100000.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HeadAngularSpring = 1000000.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HeadAngularDamper = 100000.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TorsoLinearVelSmoothingAcc = 10000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HeadAngularVelSmoothingAcc = 10000;

    virtual bool SetupBody() override;
    
    virtual bool SetupConstraintsAndPhysics() override;
    
};
