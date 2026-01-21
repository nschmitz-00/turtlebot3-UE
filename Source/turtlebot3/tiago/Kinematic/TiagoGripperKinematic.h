#pragma once

#include "CoreMinimal.h"

#include "TiagoArmKinematic.h"
#include "Drives/RRKinematicJointComponent.h"

#include "TiagoGripperKinematic.generated.h"

UCLASS()

class ATiagoGripperKinematic : public ATiagoArmKinematic
{
    GENERATED_BODY()
    
public:
    ATiagoGripperKinematic(const FObjectInitializer &ObjectInitializer);

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

    //Joints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* GripperLink_GripperLeftFingerLink = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* GripperLink_GripperRightFingerLink = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* GripperLeftFingerLink_GripperFingerMountL = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* GripperRightFingerLink_GripperFingerMountR = nullptr;

    //Functions
    virtual bool SetupBody() override;

    virtual bool SetupConstraintsAndPhysics() override;
};
