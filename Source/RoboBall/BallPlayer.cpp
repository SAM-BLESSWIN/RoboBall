// Fill out your copyright notice in the Description page of Project Settings.


#include "BallPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABallPlayer::ABallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Creating and Settingup Camera*/

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("MainCamera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	//Set Physics to True
	Mesh->SetSimulatePhysics(true);

	//To check for any Hit
	Mesh->OnComponentHit.AddDynamic(this, &ABallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Include Mass with Force and Impulse
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called every frame
void ABallPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Custom Input Axis Binding
	InputComponent->BindAxis("MoveForward", this, &ABallPlayer::MoveForwardCallback);
	InputComponent->BindAxis("MoveRight", this, &ABallPlayer::MoveRightCallback);

	//Custm Input Action Binding
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABallPlayer::JumpCallback);
}

void ABallPlayer::MoveForwardCallback(float value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * value;
	Mesh->AddForce(Forward);
}

void ABallPlayer::MoveRightCallback(float value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * value;
	Mesh->AddForce(Right);
}

void ABallPlayer::JumpCallback()
{
	if (JumpCount >= MaxJumpCount) return;

	const FVector Up = FVector::UpVector * JumpImpulse;
	Mesh->AddImpulse(Up);

	JumpCount++;
}

/*To check whether player reached ground*/
void ABallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	//Get Direction we hit the surface in Z axis
	const float HitDirection = Hit.Normal.Z;

	/*Debugging*/
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("Z Normal : %f"), HitDirection));

	//If its more than 0 then we have hit something below us.
	//If its less than 0 then we have hit something above us.
	//1 is flat, anything between is a slope.
	if (HitDirection > 0)
	{
		JumpCount = 0;
	}
}
