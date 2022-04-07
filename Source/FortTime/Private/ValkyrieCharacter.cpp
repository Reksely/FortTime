


#include "ValkyrieCharacter.h"

// Sets default values
AValkyrieCharacter::AValkyrieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void AValkyrieCharacter::MoveForward(float Value)
{
	if ((Controller) && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AValkyrieCharacter::MoveRight(float Value)
{
	if ((Controller) && Value != 0.0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator RollRotation(0, Rotation.Roll, 0);

		const FVector Direction = FRotationMatrix(RollRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
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

}

// Called to bind functionality to input
void AValkyrieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &AValkyrieCharacter::MoveForward);
	PlayerInputComponent->BindAxis("moveRight", this, &AValkyrieCharacter::MoveRight);
}

