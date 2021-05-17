// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "D_Box.generated.h"

UCLASS()
class CGEARS_API AD_Box : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AD_Box();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnyWhere)
	class UHealthComponent* MyHealth = nullptr;
	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* Mesh = nullptr;

	UFUNCTION()
		void Danneggiato(
			UHealthComponent* CompHealth,
			float Health,
			float DeltaHelath,
			const class UDamageType* DamageType,
			class AController* Controller,
			AActor* DamageCauser);


	class UDestructibleComponent* Destructible;
};
