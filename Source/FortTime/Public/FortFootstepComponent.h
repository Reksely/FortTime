

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "FortFootstepComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), config=Game )
class FORTTIME_API UFortFootstepComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFortFootstepComponent();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Footsteps")
		USoundCue* WalkFootstepCue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Footsteps")
		USoundCue* RunFootstepCue;

	UFUNCTION(BlueprintCallable, Category = "FortFootsteps")
		void PlayFootstep();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UAudioComponent* FootStep;

		
};
