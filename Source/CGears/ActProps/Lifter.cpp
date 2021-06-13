// Fill out your copyright notice in the Description page of Project Settings.


#include "Lifter.h"

// Sets default values
ALifter::ALifter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	distance = 300;

	stato    = 0;

	mode     = 0;

	active   = false;

	Stat = CreateDefaultSubobject<USceneComponent>(TEXT("Stat"));
	RootComponent = Stat;

	Mov = CreateDefaultSubobject<USceneComponent>(TEXT("Mov"));
	Mov->SetupAttachment(Stat);


	FName upper[3] = { "Base","handle","console"};

	for (int i = 0; i < 3; i++)
	{
		Mobile.Add(CreateDefaultSubobject<UStaticMeshComponent>(upper[i]));
		Mobile[i]->SetupAttachment(Mov);
	}

	FName down[6] = { "Start","Exhandle","Tile0","Tile1","Tile2","Tile3"};

	for (int i = 0; i < 6; i++)
	{
		Static.Add(CreateDefaultSubobject<UStaticMeshComponent>(down[i]));
		Static[i]->SetupAttachment(Stat);
	}

}

// Called when the game starts or when spawned
void ALifter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALifter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

