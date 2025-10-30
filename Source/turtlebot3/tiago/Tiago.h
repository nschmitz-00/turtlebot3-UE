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
#include "Robots/Tiago/TiagoBase.h"
#include "TiagoOld.generated.h"

/**
 * @brief Child class of #ARRBaseRobot
 * Uses #UDifferentialDrifeComponent
 * This class is designed to be interitted from Blueprint class to be assgined UStaticMeshComponent
 */
UCLASS()
class RAPYUTASIMULATIONPLUGINS_API ATiagoOld : public ATiagoBase
{
    GENERATED_BODY()

public:
    /**
     * @brief Construct a new ATiago object. Calls #SetupBody
     *
     * @param ObjectInitializer
     */
    ATiagoOld(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_WheelLeft = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPhysicsConstraintComponent* Base_WheelRight = nullptr;

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

    /**
     * @brief Setup #UDifferentialDriveComponent
     *
     */
    void SetupWheelDrives() override;
};