


#include "FortAnimInstanceTest.h"
#include "Kismet/KismetMathLibrary.h"
#include "ValkyrieCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetStringLibrary.h"

UFortAnimInstanceTest::UFortAnimInstanceTest()
{
	Speed = 0.0;
	Direction = 0.0;
	bIsSprinting = false;
	bIsFalling = false;
}

void UFortAnimInstanceTest::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	AActor* OwningActor = GetOwningActor();
	APawn* OwningPawn = TryGetPawnOwner();
	AValkyrieCharacter* OwningCharacter = Cast<AValkyrieCharacter>(TryGetPawnOwner());

	if (OwningActor != nullptr)
	{
		Speed = OwningActor->GetVelocity().Size();
	}

	if (OwningPawn != nullptr)
	{
		Direction = GetPawnDirection(); //Direction
		FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(OwningPawn->GetBaseAimRotation(), OwningPawn->GetActorRotation());//Delta
		Pitch = Delta.Pitch;//Pitch
		Yaw = Delta.Yaw;//Yaw
		YawDelta = UKismetMathLibrary::FInterpTo(YawDelta, UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick, OwningPawn->GetActorRotation()).Yaw / DeltaTime / 10.0, DeltaTime, 6.0);
		RotationLastTick = OwningPawn->GetActorRotation();


	}

	if (OwningCharacter != nullptr)
	{
		bIsSprinting = OwningCharacter->bIsSprinting;
		class UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(OwningCharacter->GetCharacterMovement());
		bIsFalling = MovementComponent->IsFalling();
		Gender = OwningCharacter->Gender;
		
		if (MovementComponent->GetCurrentAcceleration().Size() > 0)
		{
			bIsAccelerating = true;
		}
		else if (MovementComponent->GetCurrentAcceleration().Size() <= 0)
		{
			bIsAccelerating = false;
		}
	}
	else if (OwningCharacter == nullptr)
	{
	}
}

float UFortAnimInstanceTest::GetPawnDirection()
{
	APawn* OwningPawn = TryGetPawnOwner();

	if (Speed != 0)
	{
		Direction = CalculateDirection(OwningPawn->GetVelocity(), OwningPawn->GetControlRotation());
		return Direction;
	}
	else
	{
		return Direction;
	}
}
