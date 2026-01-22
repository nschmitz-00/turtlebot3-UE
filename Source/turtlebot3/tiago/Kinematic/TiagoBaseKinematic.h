#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "Robots/RRBaseRobot.h"
#include "Sensors/RR2DLidarComponent.h"
#include "Drives/RRDifferentialDriveComponent.h"
#include "Drives/RRPhysicsJointComponent.h"
#include "turtlebot3/ROS2Nodes/ROS2AudioNode.h"
#include "../Tools/MovingSoundComponent.h"
#include "TiagoKinematicROS2Interface.h"
#include "Drives/RRKinematicJointComponent.h"

#include "TiagoBaseKinematic.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTiagoKinematic, Log, All);

UCLASS()

class ATiagoBaseKinematic : public ARRBaseRobot
{
    GENERATED_BODY()
    
public:
    ATiagoBaseKinematic(const FObjectInitializer& ObjectInitializer);

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UROS2AudioNode* AudioNode = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMovingSoundComponent* MovingSoundComponent = nullptr;

    //Constraints
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_LidarSensor = nullptr;
    
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Base_SuspensionLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URRKinematicJointComponent* Base_SuspensionRight = nullptr;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelRadius = 9.85f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelSeparationHalf = 20.22f;

    UPROPERTY(VisibleAnywhere)
    uint8 bBodyComponentsCreated : 1;

    UFUNCTION()
    virtual bool SetupConstraintsAndPhysics();

    UFUNCTION()
    virtual void SetupWheelDrives();
    
};
