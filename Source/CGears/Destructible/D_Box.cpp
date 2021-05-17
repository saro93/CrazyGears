// Fill out your copyright notice in the Description page of Project Settings.


#include "D_Box.h"
#include "DestructibleComponent.h"
//#include "../DestructibleProp.h"
#include "../Componenti/HealthComponent.h"

// Sets default values
AD_Box::AD_Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyHealth = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	Destructible = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AD_Box::BeginPlay()
{
	Super::BeginPlay();
	MyHealth->OnHpChange.AddDynamic(this, &AD_Box::Danneggiato);
}

// Called every frame
void AD_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AD_Box::Danneggiato(UHealthComponent* CompHealth, float Health, float DeltaHelath, const UDamageType* DamageType, AController* Controller, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Error, TEXT("Colpito"));

}

