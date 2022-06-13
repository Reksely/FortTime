

#pragma once

#include "CoreMinimal.h"
#include "Public/FortItemDefinition.h"
#include "FortTime.generated.h"

UENUM(BlueprintType)
enum EFortCustomGender
{
	Male UMETA(DisplayName = "Male"),
	Female UMETA(DisplayName = "Female"),
	Both UMETA(DisplayName = "Both"),
};

UENUM(BlueprintType)
enum EFortRarity
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
	Mythic UMETA(DisplayName = "Mythic"),
	Transcendent UMETA(DisplayName = "Transcendent"),
};


USTRUCT(BlueprintType)
struct FFortItemEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int Count;
	UPROPERTY(BlueprintReadWrite)
	int PreviousCount;
	UPROPERTY(BlueprintReadWrite)
	UFortItemDefinition* ItemDefinition;
	UPROPERTY(BlueprintReadWrite)
	float Durability;
	UPROPERTY(BlueprintReadWrite)
	int Level;
	UPROPERTY(BlueprintReadWrite)
	int LoadedAmmo;


	FFortItemEntry()
	{

	}

};


