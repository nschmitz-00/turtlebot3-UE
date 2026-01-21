#pragma once

#include "CoreMinimal.h"

#include "TiagoArm.h"
#include "Drives/RRPhysicsJointComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "TiagoGripper.generated.h"

UCLASS()

class RAPYUTASIMULATIONPLUGINS_API ATiagoGripper : public ATiagoArm
{
    GENERATED_BODY()
    
public:
    ATiagoGripper(const FObjectInitializer &ObjectInitializer);

protected:
    //Meshes
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* GripperLink = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* GripperLeftFingerLink = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* GripperRightFingerLink = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* GripperFingerMountL = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* GripperFingerMountR = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* GripperFingerL1 = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* GripperFingerR1 = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* GripperFingerR2 = nullptr;

    //Constraints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* ArmTool_GripperLink = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* GripperFingerMountL_GripperFingerL1 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* GripperFingerMountR_GripperFingerR1 = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* GripperFingerMountR_GripperFingerR2 = nullptr;

    //Joints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* GripperLink_GripperLeftFingerLink = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* GripperLink_GripperRightFingerLink = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* GripperLeftFingerLink_GripperFingerMountL = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* GripperRightFingerLink_GripperFingerMountR = nullptr;
    
    //Constants
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GripperLinearSpring = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GripperLinearDamper = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GripperAngularSpring = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GripperAngularDamper = 100.f;

    //Functions
    virtual bool SetupBody() override;

    virtual bool SetupConstraintsAndPhysics() override;
};
