

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FortCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FORTTIME_API UFortCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test")
		float MaxTacticalSprintSpeed;

	UFUNCTION(Exec)
	void UseTacticalSprint();
};
