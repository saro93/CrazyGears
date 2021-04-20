// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Granata.generated.h"

UCLASS()
class CGEARS_API AGranata : public AActor
{
	GENERATED_BODY()
	
		UPROPERTY(VisibleAnyWhere, Category = "Weapon")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnyWhere, Category = "Weapon")
		class UProjectileMovementComponent* Movement;


public:	
	// Sets default values for this actor's properties
	AGranata();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
