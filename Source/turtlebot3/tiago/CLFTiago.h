#pragma once

// UE Imports
#include "CoreMinimal.h"

//RapyutaSimulationPlugins
#include "CLFTiagoBase.h"
#include "Drives/RRDifferentialDriveComponent.h"
#include "Drives/RRPhysicsJointComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
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

    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* Base_CasterBase1 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* CasterBase1_CasterRoll1 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* Base_CasterBase2 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* CasterBase2_CasterRoll2 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* Base_CasterBase3 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* CasterBase3_CasterRoll3 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* Base_CasterBase4 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* CasterBase4_CasterRoll4 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* TorsoLift_HeadBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* HeadBase_HeadTop = nullptr;

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

    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* Arm6_GripperLink = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* GripperLink_GripperLeftFingerLink = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* GripperLink_GripperRightFingerLink = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* GripperLeftFingerLink_GripperFingerMountL = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // URRPhysicsJointComponent* GripperRightFingerLink_GripperFingerMountR = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // UPhysicsConstraintComponent* GripperFingerMountL_GripperFingerL1 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // UPhysicsConstraintComponent* GripperFingerMountR_GripperFingerR1 = nullptr;
    //
    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // UPhysicsConstraintComponent* GripperFingerMountR_GripperFingerR2 = nullptr;

    

    bool SetupBody() override;

    bool SetupConstraintsAndPhysics() override;

    void SetupWheelDrives() override;
    
};


