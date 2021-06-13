// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lifter.generated.h"

UCLASS()
class CGEARS_API ALifter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALifter();

	int32 stato;

	UPROPERTY(EditAnyWhere)
	int32 mode = 0;

	UPROPERTY(EditAnyWhere)
	float distance;

	bool active;

	UPROPERTY(VisibleAnyWhere)
	USceneComponent* Stat;

	UPROPERTY(VisibleAnyWhere)
	USceneComponent* Mov;

	UPROPERTY(VisibleAnyWhere)
	TArray<UStaticMeshComponent*> Mobile;

	UPROPERTY(VisibleAnyWhere)
	TArray<UStaticMeshComponent*> Static;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
