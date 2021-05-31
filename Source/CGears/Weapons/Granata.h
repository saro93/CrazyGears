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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEsplosione>Boom;


public:	
	// Sets default values for this actor's properties
	AGranata();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
