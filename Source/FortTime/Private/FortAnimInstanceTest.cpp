


#include "FortAnimInstanceTest.h"
#include "Kismet/KismetMathLibrary.h"

UFortAnimInstanceTest::UFortAnimInstanceTest()
{
	Speed = 0.0;
	Direction = 0.0;
}

void UFortAnimInstanceTest::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	AActor* OwningActor = GetOwningActor();
	APawn* OwningPawn = TryGetPawnOwner();

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
