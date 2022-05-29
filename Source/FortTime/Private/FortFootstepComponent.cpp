


#include "FortFootstepComponent.h"

// Sets default values for this component's properties
UFortFootstepComponent::UFortFootstepComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UFortFootstepComponent::PlayFootstep()
{
	FootStep->Play();
}

// Called when the game starts
void UFortFootstepComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFortFootstepComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FootStep->SetSound(WalkFootstepCue);

	// ...
}

