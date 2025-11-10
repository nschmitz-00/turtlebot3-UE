#pragma once

// UE imports
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// RSP imports
#include "Robots/RRBaseRobot.h"
#include "Sensors/RR2DLidarComponent.h"

#include "CLFTiagoROS2Interface.h"

#include "CLFTiagoBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCLFTiago, Log, All);

UCLASS()
class RAPYUTASIMULATIONPLUGINS_API ACLFTiagoBase : public ARRBaseRobot
{
    GENERATED_BODY()

public:
    ACLFTiagoBase(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void PostInitializeComponents() override;

    UFUNCTION()
    virtual bool SetupBody();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Base = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* BaseRing = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* LidarSensor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URR2DLidarComponent* LidarComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* WheelLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* WheelRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* TorsoFix = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* AntennaLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* AntennaRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* TorsoInnerBox = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* TorsoLiftWithArm = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* HeadBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* HeadTop = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_LidarSensor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_BaseRing = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_TorsoFix = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_AntennaLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_AntennaRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_TorsoInnerBox = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxForce = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* BodyMaterial = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* BodyAccentMaterial = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* WheelMaterial = nullptr;

    UPROPERTY(VisibleAnywhere)
    uint8 bBodyComponentsCreated : 1;

    UFUNCTION()
    virtual bool SetupConstraintsAndPhysics();

    UFUNCTION()
    virtual void SetupWheelDrives();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelRadius = 19.5f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelSeparationHalf = 20.22f;
};
