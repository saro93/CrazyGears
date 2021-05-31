// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(
FOnHPChangeSignature,
UHealthComponent*, CompHealth,
float, Health,
float, DeltaHelath,
const class UDamageType*, DamageType,
class AController*, Controller,
	AActor*, DamageCauser);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CGEARS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = "Game|Damage")
		FOnHPChangeSignature OnHpChange;

	UPROPERTY(BlueprintReadWrite,Category = "Health")
		float resistenza;

	UPROPERTY( BlueprintReadWrite, Category = "Health")
	    float vitalita;

	UPROPERTY( BlueprintReadWrite, Category = "Health")
		float energia;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float Maxresistenza;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float Maxvitalita;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float Maxenergia;

	UFUNCTION(BlueprintPure)
	FORCEINLINE	float GetEnergyPercent() { return energia / Maxenergia; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE	float GetVitalityPercent() { return vitalita / Maxvitalita; };

	bool balive;

	bool bactive;

	UFUNCTION()
	void Colpito(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;




		
};
