// Fill out your copyright notice in the Description page of Project Settings.


#include "Esplosione.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AEsplosione::AEsplosione()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RaggioEsplosione = 50;

	Point = CreateDefaultSubobject<USceneComponent>(TEXT("Centro"));
	RootComponent = Point;
	ForzaEsplosiva = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForzaEsplosiva"));
	ForzaEsplosiva->SetupAttachment(Point);
}

// Called when the game starts or when spawned
void AEsplosione::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugSphere(GetWorld(),GetActorLocation(),RaggioEsplosione,10,FColor::Blue,false,3.f);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Effetto,GetActorLocation());
	ForzaEsplosiva->Radius = RaggioEsplosione;
	
	ForzaEsplosiva->FireImpulse();

}

// Called every frame
void AEsplosione::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

