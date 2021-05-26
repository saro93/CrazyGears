// Fill out your copyright notice in the Description page of Project Settings.


#include "D_Box.h"
#include "DestructibleComponent.h"
#include "Components/BoxComponent.h"
#include "../Componenti/HealthComponent.h"

// Sets default values
AD_Box::AD_Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	MyHealth = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	Destructible = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible"));
	Destructible->SetNotifyRigidBodyCollision(true);

	Trigger->SetupAttachment(RootComponent);
	Destructible->SetupAttachment(RootComponent);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Hitted"));

}

