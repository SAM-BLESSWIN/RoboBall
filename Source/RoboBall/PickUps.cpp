// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps.h"
#include "RoboBall/BallPlayer.h"
#include "RoboBall/RoboBallGameModeBase.h"

// Sets default values
APickUps::APickUps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &APickUps::OverlapBegin);
}

// Called when the game starts or when spawned
void APickUps::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUps::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check whether the hit Actor is Player
	if (Cast<ABallPlayer>(OtherActor) != nullptr)
	{
		Collected();  //Calls the event implemented in Blueprint
	}
}

void APickUps::Collected_Implementation() 
{
	//Called from Blueprint
	ARoboBallGameModeBase* GameMode = Cast<ARoboBallGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->ItemCollected();
	}
}

