// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CGEARS_API AWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnyWhere)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnyWhere)
	float FireRate;

	UPROPERTY(EditAnyWhere)
	float Damage;



public:	
	// Sets default values for this actor's properties
	AWeapon();

	class UHealthComponent* OwnerHealth;

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetFireRate() { return FireRate; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetDamage() { return Damage; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE USkeletalMeshComponent* GetWeapon() { return Weapon; }

	UPROPERTY(BlueprintReadOnly)
	bool Aggancio;

	virtual void Fire();

	bool AimingTrace(FHitResult &OutHit, FVector &HitLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere)
	float Consumo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditdefaultsOnly, Category = "Weapon")
		UParticleSystem* FrontFire;

	UPROPERTY(EditdefaultsOnly, Category = "Weapon")
		UParticleSystem* Scia;

	UPROPERTY(EditdefaultsOnly, Category = "Weapon")
		TArray<UParticleSystem*> ImpactEffects;

};
