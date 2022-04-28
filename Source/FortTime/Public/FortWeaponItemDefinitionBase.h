

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FortWeaponItemDefinitionBase.generated.h"

/**
 * 
 */
UCLASS()
class FORTTIME_API UFortWeaponItemDefinitionBase : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Info")
		USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Info")
		float MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Info")
		bool bPROTO;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Info")
		UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Info")
		AActor* WeaponActor;

	
};
