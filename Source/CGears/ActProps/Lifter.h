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

	bool  Active;

	int32 stato;

	float delay;

	UPROPERTY(EditAnyWhere)
	int32 mode = 0; // 0 = deactivated // 1 = work on call // 2 = work on time

	UPROPERTY(EditAnyWhere)
	float distance;

	bool active;

	UPROPERTY(VisibleAnyWhere)
	USceneComponent* Stat;

	UPROPERTY(VisibleAnyWhere)
	USceneComponent* Mov;



	class ACGearsRobot* Key = nullptr;

	UPROPERTY(VisibleAnyWhere)
    class UBoxComponent* terminalA;

	UPROPERTY(VisibleAnyWhere)
	      UBoxComponent* terminalB;

	UPROPERTY(VisibleAnyWhere)
	TArray<UStaticMeshComponent*> Mobile;

	UPROPERTY(VisibleAnyWhere)
	TArray<UStaticMeshComponent*> Static;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Activate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DeActivate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere)
	USoundBase* SMove;

	UPROPERTY(EditAnyWhere)
	USoundBase* SStop;

	class UAudioComponent* SActual = nullptr;

};
