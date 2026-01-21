#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"

#include "MovingSoundComponent.generated.h"

UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))

class UMovingSoundComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UMovingSoundComponent();
    virtual void TickComponent(float DeltaTime,
                               ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* ParentActor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundWave* SoundFile = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAudioComponent* AudioComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VelocityThreshold = 0.2;

private:
    bool currentlyPlaying = false;
};