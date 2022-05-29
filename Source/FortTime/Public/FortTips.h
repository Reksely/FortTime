

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FortTips.generated.h"

/**
 * 
 */
UCLASS()
class FORTTIME_API UFortTips : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tips")
		TArray<FName> Tips;
	
};
