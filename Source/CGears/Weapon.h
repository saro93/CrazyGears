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
		int32 Ammo;

	UPROPERTY(EditAnyWhere)
		int32 MaxAmmo;

	UPROPERTY(EditAnyWhere)
		float FireRate;

	UPROPERTY(EditAnyWhere)
		float Damage;


public:	
	// Sets default values for this actor's properties
	AWeapon();

	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetAmmo() { return Ammo; }
	
	UFUNCTION(BlueprintPure)
		FORCEINLINE int32 GetMaxAmmo() { return MaxAmmo; }
	
	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetFireRate() { return FireRate; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE float GetDamage() { return Damage; }

	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditdefaultsOnly, Category = "Weapon")
		UParticleSystem* FrontFire;

	UPROPERTY(EditdefaultsOnly, Category = "Weapon")
		UParticleSystem* Scia;

};
