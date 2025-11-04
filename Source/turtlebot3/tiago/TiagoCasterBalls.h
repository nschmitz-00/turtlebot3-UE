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
#include "Drives/DifferentialDriveComponent.h"
#include "TiagoBase.h"
#include "TiagoCasterBalls.generated.h"

/**
 * @brief Child class of #ARRBaseRobot
 * Uses #UDifferentialDrifeComponent
 * This class is designed to be interitted from Blueprint class to be assgined UStaticMeshComponent
 */
UCLASS()
class RAPYUTASIMULATIONPLUGINS_API ATiagoCasterBalls : public ATiagoBase
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