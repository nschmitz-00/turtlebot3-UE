#pragma once

// UE Imports
#include "CoreMinimal.h"

//RapyutaSimulationPlugins
#include "CLFTiagoBase.h"
#include "Drives/RRDifferentialDriveComponent.h"
#include "Drives/RRPhysicsJointComponent.h"
#include "Robots/RRBaseRobot.h"

#include "CLFTiago.generated.h"

UCLASS()
class RAPYUTASIMULATIONPLUGINS_API ACLFTiago : public ACLFTiagoBase
{
    GENERATED_BODY()

public:

    ACLFTiago(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_WheelLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_WheelRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_TorsoLift = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* TorsoLift_HeadBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* HeadBase_HeadTop = nullptr;

    bool SetupBody() override;

    bool SetupConstraintsAndPhysics() override;

    void SetupWheelDrives() override;
    
};


