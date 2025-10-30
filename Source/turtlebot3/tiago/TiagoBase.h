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
#include "Robots/Tiago/RRTiagoROS2InterfaceOld.h"
#include "Sensors/RR2DLidarComponent.h"
#include "TiagoBaseOld.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTiago, Log, All);

/**
 * @brief Base class for Tiago robot
 */
UCLASS()

class RAPYUTASIMULATIONPLUGINS_API ATiagoBaseOld : public ARRBaseRobot
{
    GENERATED_BODY()

public:
    /**
    *  @brief Construct a new ATiagoBase object. Calls #SetupBody
    *
    * @param ObjectInitializer
    */
    ATiagoBaseOld(const FObjectInitializer& ObjectInitializer);

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
    UStaticMeshComponent* CasterBackLeftBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBackRightBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterFrontLeftBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterFrontRightBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBackLeftWheel = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterBackRightWheel = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterFrontLeftWheel = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMeshComponent* CasterFrontRightWheel = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_LidarSensor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_BaseRing = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_CasterBackLeftBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_CasterBackRightBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_CasterFrontLeftBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_CasterFrontRightBase = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* CasterBackLeftBase_CasterBackLeftWheel = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* CasterBackRightBase_CasterBackRightWheel = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* CasterFrontLeftBase_CasterFrontLeftWheel = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* CasterFrontRightBase_CasterFrontRightWheel = nullptr;

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