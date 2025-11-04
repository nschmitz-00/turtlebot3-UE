/**
 * @file TiagoBase.h
 * @brief Tiago implementation base class
*/
#pragma once

// UE
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

//RapyutaSimulationPlugins
#include "Robots/RRBaseRobot.h"
#include "RRTiagoROS2Interface.h"
#include "Sensors/RR2DLidarComponent.h"
#include "TiagoBase.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTiago, Log, All);

/**
 * @brief Base class for Tiago robot
 */
UCLASS()

class RAPYUTASIMULATIONPLUGINS_API ATiagoBase : public ARRBaseRobot
{
    GENERATED_BODY()

public:
    /**
    *  @brief Construct a new ATiagoBase object. Calls #SetupBody
    *
    * @param ObjectInitializer
    */
    ATiagoBase(const FObjectInitializer& ObjectInitializer);

protected:
    /**
     * @brief calls #SetupWheelDrives
     *
     */
    virtual void PostInitializeComponents() override;

    /**
     * @brief Create UStaticMeshComponent, create UPhysicsConstraintComponent
     *
     */
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
    UPhysicsConstraintComponent* Base_WheelLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_WheelRight = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_LidarSensor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_BaseRing = nullptr;


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxForce = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMaterial* BallMaterial = nullptr;

    UPROPERTY(VisibleAnywhere)
    uint8 bBodyComponentsCreated : 1;

    /**
     * @brief Setup UPhysicsConstraintComponent.
     *
     */
    UFUNCTION()
    virtual bool SetupConstraintsAndPhysics();

    /**
     * @brief Setup #UDifferentialDriveComponent
     *
     */
    UFUNCTION()
    virtual void SetupWheelDrives();

    //! pass to #UDifferentialDriveComponent
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelRadius = 19.5f;

    //! pass to #UDifferentialDriveComponent
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WheelSeparationHalf = 20.22f;
};