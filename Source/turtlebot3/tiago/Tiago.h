/**
 * @file Tiago.h
 * @brief Child class of #ARRBaseRobot
 *
 */

#pragma once

//UE
#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

//RapyutaSimulationPlugins
#include "Drives/DifferentialDriveComponent.h"
#include "TiagoBase.h"
#include "Tiago.generated.h"

/**
 * @brief Child class of #ARRBaseRobot
 * Uses #UDifferentialDrifeComponent
 * This class is designed to be interitted from Blueprint class to be assgined UStaticMeshComponent
 */
UCLASS()
class RAPYUTASIMULATIONPLUGINS_API ATiago : public ATiagoBase
{
    GENERATED_BODY()

public:
    /**
     * @brief Construct a new ATiago object. Calls #SetupBody
     *
     * @param ObjectInitializer
     */
    ATiago(const FObjectInitializer& ObjectInitializer);

protected:
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

    /**
     * @brief Create UStaticMeshComponent, create UPhysicsConstraintComponent
     *
     */
    bool SetupBody() override;

    /**
     * @brief Setup material, relative location, angular/linear limits, drive params.
     *
     */
    bool SetupConstraintsAndPhysics() override;
};