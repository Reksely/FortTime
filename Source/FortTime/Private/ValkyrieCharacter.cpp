


#include "ValkyrieCharacter.h"
#include "FortCharacterMovementComponent.h"
#include "Math/Color.h"
#include "Animation/AnimInstance.h"
#include "FortWeaponItemDefinitionBase.h"
#include "FortFunctionLibrary.h"
#include "FortGameInstanceBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AValkyrieCharacter::AValkyrieCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UFortCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Disabled;

	//components setup
	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(GetMesh());
	CharacterMesh->SetWorldLocation(FVector(0.0, 0.0, -90.0), false);
	PROTO_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponPROTO"));
	PROTO_Weapon->SetupAttachment(CharacterMesh, TEXT("weapon_r"));
	PROTO_Weapon->SetRelativeScale3D(FVector(0.01, 0.01, 0.01));

}

void AValkyrieCharacter::MoveForward(float Value)
{
	if ((Controller) && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		ForwardAxis = Value;
	}
}

//yaw input
void AValkyrieCharacter::MoveRight(float Value)
{
	if ((Controller) && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AValkyrieCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

//pitch input
void AValkyrieCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AValkyrieCharacter::SetWantsToSprint()
{
	bWantsToSprint = true;
}

void AValkyrieCharacter::SetDoesNotWantToSprint()
{
	bWantsToSprint = false;
}

void AValkyrieCharacter::Sprint(float SprintSpeed)
{
	class UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	MovementComponent->MaxWalkSpeed = SprintSpeed;
	bIsSprinting = true;
}

void AValkyrieCharacter::StopSprinting(float WalkSpeed)
{
	class UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	MovementComponent->MaxWalkSpeed = WalkSpeed;
	bIsSprinting = false;
}

//better print string (print string 2.0)
void AValkyrieCharacter::canone(FString Message, float Time, EFortColors Color)
{
	FColor Colore = FColor::Cyan;
	
	if (Color == EFortColors::Green)
	{
		Colore = FColor::Green;
	}
	if (Color == EFortColors::Red)
	{
		Colore = FColor::Red;
	}
	if (Color == EFortColors::Cyan)
	{
		Colore = FColor::Cyan;
	}
	if (Color == EFortColors::Black)
	{
		Colore = FColor::Black;
	}
	if (Color == EFortColors::Blue)
	{
		Colore = FColor::Blue;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, Colore, Message);
	}
}

void AValkyrieCharacter::ChooseParts(USkeletalMesh* MeshToSet, UClass* AnimInstance, EFortCustomGender NewGender)
{
	class USkeletalMeshComponent* PlayerMesh = CharacterMesh;

	if (MeshToSet != nullptr)
	{
		PlayerMesh->SetSkeletalMesh(MeshToSet, true);
		PlayerMesh->SetAnimInstanceClass(AnimInstance);
		Gender = NewGender;

	}
}

void AValkyrieCharacter::EquipWID(UFortWeaponItemDefinitionBase* WID)
{
	PROTO_Weapon->SetSkeletalMesh(WID->WeaponMesh, true);
	PlayAnimMontage(WID->EquipMontage, 1.0, NAME_None);
	FVector SpawnLoc = K2_GetActorLocation();
}

bool AValkyrieCharacter::CanSprint()
{
	if (ForwardAxis == 1.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AValkyrieCharacter::Cane(UFortWeaponItemDefinitionBase* Weapon)
{
	class USkeletalMeshComponent* PlayerMesh = GetMesh();

	PlayAnimMontage(Weapon->EquipMontage, 1.0f, NAME_None);

	const FVector Location = GetActorLocation();

	const FRotator Rotation = GetActorRotation();

	const AActor* WeaponActor = Weapon->WeaponActor;

	//GetWorld()->SpawnActor(WeaponActor, Location, Rotation);

	PROTO_Weapon->SetSkeletalMesh(Weapon->WeaponMesh);
}

// Called when the game starts or when spawned
void AValkyrieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AValkyrieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWantsToSprint == true && CanSprint() == true)
	{
		Sprint(550.0);
	}
	else if (bWantsToSprint == false || CanSprint() == false)
	{
		StopSprinting(410.0);
	}

}

// Called to bind functionality to input
void AValkyrieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &AValkyrieCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AValkyrieCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AValkyrieCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AValkyrieCharacter::LookUp);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AValkyrieCharacter::SetWantsToSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AValkyrieCharacter::SetDoesNotWantToSprint);
}

