

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ValkyrieCharacter.generated.h"

UCLASS()
class FORTTIME_API AValkyrieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AValkyrieCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Function to move forward/backward the character
	void MoveForward(float Value);

	//function to move right/left the character
	void MoveRight(float Value);
};
