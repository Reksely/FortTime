


#include "FortPickup.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFortPickup::AFortPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(GetRootComponent());
	TouchInput = CreateDefaultSubobject<UBoxComponent>(TEXT("TouchInput"));
	TouchInput->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AFortPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFortPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFortPickup::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFortPickup, ItemDefinition);
}

