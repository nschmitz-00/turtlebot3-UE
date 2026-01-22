#pragma once

#include "CoreMinimal.h"

#include "TiagoBaseKinematic.h"
#include "Drives/RRKinematicJointComponent.h"

#include "TiagoTorsoKinematic.generated.h"

UCLASS()

class ATiagoTorsoKinematic : public ATiagoBaseKinematic
{
    GENERATED_BODY()
    
public:
    ATiagoTorsoKinematic(const FObjectInitializer& ObjectInitializer);

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

    //Joints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Base_TorsoLift = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* TorsoLift_HeadBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* HeadBase_HeadTop = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialPosTorsoLiftInMeters = 0.15;

    virtual bool SetupBody() override;

    virtual bool SetupConstraintsAndPhysics() override;
    
};
