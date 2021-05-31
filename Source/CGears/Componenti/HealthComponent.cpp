// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Maxresistenza = 100;
	Maxenergia    = 100;
	Maxvitalita   = 100;
	bactive = true;
	balive  = true;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	resistenza = Maxresistenza;
	energia    = Maxenergia;
	vitalita   = Maxvitalita;

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::Colpito);

	}

}


void UHealthComponent::Colpito(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	vitalita = vitalita - Damage;
	if (vitalita < 0) vitalita = 0;
	//if (Health == 0) GetOwner()->Destroy();
	UE_LOG(LogTemp, Log, TEXT("la vitalita' è ora %f"), vitalita);

	OnHpChange.Broadcast(this, vitalita, Damage, DamageType, InstigatedBy, DamageCauser);

}


