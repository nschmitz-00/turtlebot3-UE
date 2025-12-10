#pragma once

// UE imports
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// RSP imports
#include "Robots/RRBaseRobot.h"
#include "Sensors/RR2DLidarComponent.h"
#include "Drives/RRDifferentialDriveComponent.h"
#include "Drives/RRPhysicsJointComponent.h"

#include "CLFTiagoROS2Interface.h"

#include "TiagoBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTiago, Log, All);

UCLASS()

class RAPYUTASIMULATIONPLUGINS_API ATiagoBase : public ARRBaseRobot
{
    GENERATED_BODY()
    
public:
    ATiagoBase(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void PostInitializeComponents() override;

    UFUNCTION()
    virtual bool SetupBody();

    //Meshes
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Base = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* BaseRing = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* LidarSensor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* WheelLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* WheelRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* AntennaLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* AntennaRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBaseBackLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterRollBackLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBaseBackRight = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterRollBackRight = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBaseFrontLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterRollFrontLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBaseFrontRight = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterRollFrontRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* SonarLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* SonarCenter = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* SonarRight = nullptr;
    
    //Functional Components
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URR2DLidarComponent* LidarComponent = nullptr;

    //Constraints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_LidarSensor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_BaseRing = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_AntennaLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_AntennaRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_SonarLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_SonarCenter = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_SonarRight = nullptr;
    
    //Joints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_WheelLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_WheelRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_CasterBaseBackLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* CasterBaseBackLeft_CasterRollBackLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_CasterBaseBackRight = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* CasterBaseBackRight_CasterRollBackRight = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_CasterBaseFrontLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* CasterBaseFrontLeft_CasterRollFrontLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* Base_CasterBaseFrontRight = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRPhysicsJointComponent* CasterBaseFrontRight_CasterRollFrontRight = nullptr;

    //Variables
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxForce = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CasterBaseAngularSpring = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CasterBaseAngularDamper = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CasterRollAngularSpring = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CasterRollAngularDamper = 10.f;

    UPROPERTY(VisibleAnywhere)
    uint8 bBodyComponentsCreated : 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelRadius = 19.5f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelSeparationHalf = 20.22f;

    UFUNCTION()
    virtual bool SetupConstraintsAndPhysics();

    UFUNCTION()
    virtual void SetupWheelDrives();
};
