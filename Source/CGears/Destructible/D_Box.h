// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "D_Box.generated.h"

UCLASS()
class CGEARS_API AD_Box : public AActor
{
	GENERATED_BODY()
	

	UPROPERTY(VisibleAnyWhere)
		class UHealthComponent* MyHealth = nullptr;

	UPROPERTY(VisibleAnyWhere)
		class UBoxComponent* Trigger = nullptr;

	UPROPERTY(VisibleAnyWhere)
		class UDestructibleComponent* Destructible;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	AD_Box();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Danneggiato(
			UHealthComponent* CompHealth,
			float Health,
			float DeltaHelath,
			const class UDamageType* DamageType,
			class AController* Controller,
			AActor* DamageCauser);


};
