// Fill out your copyright notice in the Description page of Project Settings.


#include "Torretta.h"
#include "Components/BoxComponent.h"

// Sets default values
ATorretta::ATorretta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshBase=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	PiattoMobile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Piatto"));
	Cannoni = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannoni"));

	MeshBase->SetupAttachment(RootComponent);
	PiattoMobile->SetupAttachment(MeshBase);
	Cannoni->SetupAttachment(MeshBase);

	boxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Collisione"));
	boxCol->SetupAttachment(MeshBase);

}

// Called when the game starts or when spawned
void ATorretta::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATorretta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

