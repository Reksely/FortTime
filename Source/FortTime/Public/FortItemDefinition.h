

#pragma once

#include "CoreMinimal.h"
#include <FortTime/FortTime.h>
#include "Engine/DataAsset.h"
#include "FortItemDefinition.generated.h"
/**
 * 
 */
UCLASS()
class FORTTIME_API UFortItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info|Rarity")
		TEnumAsByte<EFortRarity> Rarity;
	
};
