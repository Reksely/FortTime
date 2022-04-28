

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FortWeaponItemDefinitionBase.h"
#include <FortTime/FortTime.h>
#include "ValkyrieCharacter.generated.h"

UENUM(BlueprintType)
enum EFortColors
{
	Green     UMETA(DisplayName = "Green"),
	Red      UMETA(DisplayName = "Red"),
	Cyan   UMETA(DisplayName = "Cyan"),
	White	UMETA(DisplayName = "White"),
	Blue	UMETA(DisplayName = "Blue"),
	Black	UMETA(DisplayName = "Black"),
};



UCLASS()
class FORTTIME_API AValkyrieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AValkyrieCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Valkyrie|Bools")
		bool bWantsToSprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Valkyrie|Bools")
		bool bIsSprinting;

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, Keywords = "ciao sono un coglione", AdvancedDisplay = "2", DevelopmentOnly))
		void canone(FString Message, float Time, EFortColors Color);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Custom mesh, character parts, body, head, athena, choose, "), Category = "CharacterParts")
		void ChooseParts(USkeletalMesh* MeshToSet, UClass* AnimInstance, EFortCustomGender NewGender);

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Custom mesh, character parts, body, head, athena, choose, equip, wid, weapon, item "), Category = "WeaponsBase")
		void EquipWID(UFortWeaponItemDefinitionBase* WID);

	UFUNCTION(BlueprintPure, Category = "Valkyrie|Functions")
		bool CanSprint();

	UFUNCTION(BlueprintCallable, meta = (Keywords = "Weapon, equip, athena, test, proto, montage"), Category = "WeaponsBase")
		void Cane(UFortWeaponItemDefinitionBase* Weapon);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Valkyrie")
		USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Valkyrie")
		USkeletalMeshComponent* PROTO_Weapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Valkyrie|Enums")
		TEnumAsByte<EFortCustomGender> Gender;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Valkyrie|Floats")
		float ForwardAxis;





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

	//function to let the character move the camera with yaw input
	void Turn(float Value);

	//function to let the character move the camera with pitch input
	void LookUp(float Value);

		void SetWantsToSprint();

		void SetDoesNotWantToSprint();

	UFUNCTION(BlueprintCallable)
		void Sprint(float SprintSpeed);
	
	UFUNCTION(BlueprintCallable)
		void StopSprinting(float WalkSpeed);
};
