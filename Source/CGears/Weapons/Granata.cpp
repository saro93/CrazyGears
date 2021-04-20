// Fill out your copyright notice in the Description page of Project Settings.


#include "Granata.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
AGranata::AGranata()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));


}

// Called when the game starts or when spawned
void AGranata::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGranata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

