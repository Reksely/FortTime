

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FortTime/FortTime.h"
#include "Components/BoxComponent.h"
#include "FortPickup.generated.h"

UCLASS()
class FORTTIME_API AFortPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFortPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bUsePickupWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Replicated)
		UFortItemDefinition* ItemDefinition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
		USkeletalMeshComponent* ItemMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
		UBoxComponent* TouchInput;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
