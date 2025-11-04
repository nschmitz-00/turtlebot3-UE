/**
 * @file TiagoCasterBalls.h
 * @brief Child class of #ARRBaseRobot
 *
 */

#pragma once

//UE
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

//RapyutaSimulationPlugins
#include "Robots/RRBaseRobot.h"
#include "Drives/DifferentialDriveComponent.h"
#include "Sensors/RR2DLidarComponent.h"
#include "RRTiagoROS2Interface.h"
#include "TiagoCasterBalls.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTiago, Log, All);

/**
 * @brief Child class of #ARRBaseRobot
 * Uses #UDifferentialDrifeComponent
 * This class is designed to be interitted from Blueprint class to be assgined UStaticMeshComponent
 */
UCLASS()
class RAPYUTASIMULATIONPLUGINS_API ATiagoCasterBalls : public ARRBaseRobot
{
    GENERATED_BODY()

public:
    /**
     * @brief Construct a new ATiago object. Calls #SetupBody
     *
     * @param ObjectInitializer
     */
    ATiagoCasterBalls(const FObjectInitializer& ObjectInitializer);

protected:

    virtual void PostInitializeComponents() override;

    UFUNCTION()
    virtual bool SetupBody();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* Base = nullptr;

    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // UStaticMeshComponent* BaseRing = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* LidarSensor = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    URR2DLidarComponent* LidarComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* WheelLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* WheelRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_WheelLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_WheelRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_LidarSensor = nullptr;

    // UPROPERTY(EditAnywhere, BlueprintReadWrite)
    // UPhysicsConstraintComponent* Base_BaseRing = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBallBackLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBallBackRight = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBallFrontLeft = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBallFrontRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_CasterBallBackLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_CasterBallBackRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_CasterBallFrontLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_CasterBallFrontRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxForce = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* BallMaterial = nullptr;

    UPROPERTY(VisibleAnywhere)
    uint8 bBodyComponentsCreated : 1;
    
    UFUNCTION()
    virtual bool SetupConstraintsAndPhysics();

    UFUNCTION()
    virtual void SetupWheelDrives();

    //! pass to #UDifferentialDriveComponent
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelRadius = 19.5f;

    //! pass to #UDifferentialDriveComponent
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelSeparationHalf = 20.22f;
    
};