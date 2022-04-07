

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "FortAnimInstanceTest.generated.h"

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class UFortAnimInstanceTest: public UAnimInstance
{
	GENERATED_BODY()

public:
	UFortAnimInstanceTest();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FortAnimInstance")
		float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FortAnimInstance")
		float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FortAnimInstance")
		float Pitch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FortAnimInstance")
		float Yaw;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FortAnimInstance")
		float GetPawnDirection();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FortAnimInstance")
		FRotator RotationLastTick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FortAnimInstance")
		float YawDelta;

	

	virtual void NativeUpdateAnimation(float DeltaTime) override;
};
