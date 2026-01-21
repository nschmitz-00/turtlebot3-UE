#include "MovingSoundComponent.h"

UMovingSoundComponent::UMovingSoundComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MovingSoundComponent"));
    AudioComponent->bAutoActivate = false;
    AudioComponent->SetSound(SoundFile);
    AudioComponent->SetupAttachment(this);
}

void UMovingSoundComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    float maxCurrentVelocity = ParentActor->GetVelocity().GetMax();
    if (maxCurrentVelocity > VelocityThreshold && !currentlyPlaying)
    {
        AudioComponent->Play();
        currentlyPlaying = true;
    }
    else if (maxCurrentVelocity < VelocityThreshold && currentlyPlaying)
    {
        AudioComponent->Stop();
        currentlyPlaying = false;
    }
}


void UMovingSoundComponent::BeginPlay()
{
    Super::BeginPlay();
    ParentActor = GetOwner();
}