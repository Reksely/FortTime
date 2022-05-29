

#pragma once

#include "CoreMinimal.h"

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



